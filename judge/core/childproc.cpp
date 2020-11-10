#include "childproc.hpp"

int alarmTargetPid = -1; 

int getUsedMemory(struct rusage& resource){
    int memory = static_cast<int>(resource.ru_maxrss);
    return memory;  
}


int getUsedCPUTime(struct rusage& resource){
    int userTime = static_cast<int>(resource.ru_utime.tv_sec * 1000 + resource.ru_utime.tv_usec / 1000);
    int sysTime = static_cast<int>(resource.ru_stime.tv_sec * 1000  + resource.ru_stime.tv_usec / 1000); 
    int time = userTime + sysTime; 
    return time; 
}


bool redirectFd(int sourceFd, int destFd, bool closeSrcFd){
    dup2(sourceFd, destFd); 
    if(closeSrcFd)
        close(sourceFd);
    return true;  
}


int startChildProc(string path, string cmd, vector<string> args, vector<string> env){
    const char* cpath = path.c_str(); 
    const char* ccmd = cmd.c_str(); 
    
    #ifdef DBUG
    cout << endl; 
    cout << path << endl; 
    cout << cmd << endl; 
    for(int i = 0; i < args.size(); i++){
        cout << args[i] << " "; 
    }
    #endif

    chdir(cpath); 
    vector<char*> cargs;
    cargs.push_back(const_cast<char*>(ccmd)); 
    for(int i = 0; i < args.size(); i++){
        cargs.push_back(const_cast<char*>(args[i].c_str())); 
    }
    cargs.push_back(nullptr); 
    char** readyArgs = cargs.data(); 
    //TODO - need to add for env setting 
    execvp(ccmd, &(readyArgs[0])); 
    cerr << strerror(errno) << endl; 
    return -1; 
}


bool setLimitFd(int maxFd){
    #ifdef DEBUG
    struct rlimit old_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "old limits [soft limit] = " << old_lim.rlim_cur << endl; 
        cerr << "old limits [hard limit] = " << old_lim.rlim_max << endl; 
    }
    #endif 

    struct rlimit limit; 
    limit.rlim_cur = maxFd; 
    limit.rlim_max = maxFd; 
    if(setrlimit(RLIMIT_NOFILE, &limit) == -1){
        throw runtime_error(PROC_LIMIT_FAIL); 
    }

    #ifdef DEBUG
    struct rlimit new_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "new limits [soft limit] = " << new_lim.rlim_cur << endl; 
        cerr << "new limits [hard limit] = " << new_lim.rlim_max << endl; 
    }
    #endif 
    return true; 
}


bool setLimitProcCount(int maxProc){

    #ifdef DEBUG
    struct rlimit old_lim; 
    struct rlimit old_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "old limits [soft limit] = " << old_lim.rlim_cur << endl; 
        cerr << "old limits [hard limit] = " << old_lim.rlim_max << endl; 
    }
    #endif

    struct rlimit limit; 
    limit.rlim_cur = maxProc; 
    limit.rlim_max = maxProc; 
    if(setrlimit(RLIMIT_NPROC, &limit) == -1){
        throw runtime_error(PROC_LIMIT_FAIL); 
    }

    #ifdef DEBUG
    struct rlimit new_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "new limits [soft limit] = " << new_lim.rlim_cur << endl; 
        cerr << "new limits [hard limit] = " << new_lim.rlim_max << endl; 
    }
    #endif 


    return true; 
}


bool setLimitMemory(int maxMemory){
    unsigned int byteMemory = static_cast<unsigned int>(maxMemory) * 1000'000; 
    #ifdef DEBUG
    struct rlimit old_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "old limits [soft limit] = " << old_lim.rlim_cur << endl; 
        cerr << "old limits [hard limit] = " << old_lim.rlim_max << endl; 
    }
    #endif

    struct rlimit limit; 
    limit.rlim_cur = byteMemory; 
    limit.rlim_max = byteMemory; 
    if(setrlimit(RLIMIT_AS, &limit) == -1){
        cerr << "set memory limit fail...tt" << endl; 
        throw runtime_error(PROC_LIMIT_FAIL); 
    }

    #ifdef DEBUG
    struct rlimit new_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) {
        cerr << "new limits [soft limit] = " << new_lim.rlim_cur << endl; 
        cerr << "new limits [hard limit] = " << new_lim.rlim_max << endl; 
    }
    #endif 
    return true; 
}


int killProcess(pid_t pid) {
    return kill(pid, SIGKILL);
}


void alarmHandler(int sig) 
{ 
    cerr << "time limit end kill process" << endl; 
    cerr << "kill pid : " << alarmTargetPid << endl; 
    killProcess(alarmTargetPid); 
    alarmTargetPid = -1; 
} 


bool removeLimitTime(){
    return setLimitTime(0, -1); 
}


bool setLimitTime(int maxTime, int targetPid){
    errno = 0; //clear errno 
    alarmTargetPid = targetPid; 
    
    signal(SIGALRM, alarmHandler); 
    //cerr << strerror(errno) << endl; 
    if(errno != 0){
        cerr << strerror(errno) << endl; 
        cerr << "fail to set sinal SIGALRM - alarmHandler" << endl; 
        return false; 
    }

    struct itimerval new_lim; 
    new_lim.it_interval.tv_usec = 0; 
    new_lim.it_interval.tv_sec = 0; 
    new_lim.it_value.tv_usec = (maxTime % 1000) * 1000; 
    new_lim.it_value.tv_sec = maxTime / 1000; 
    if(setitimer(ITIMER_REAL, &new_lim, NULL)  == -1) {
        cerr << strerror(errno) << endl; 
        cerr << "fail to setitmer to start timer" << endl; 
        return false; 
    }
    return true; 
}  
