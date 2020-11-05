#include "childproc.hpp"

int startChildProc(string path, string cmd, vector<string> args, vector<string> env){
    const char* cpath = path.c_str(); 
    const char* ccmd = cmd.c_str(); 
    
    /*
    cout << endl; 
    cout << path << endl; 
    cout << cmd << endl; 
    for(int i = 0; i < args.size(); i++){
        cout << args[i] << " "; 
    }
    */

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
    if( getrlimit(RLIMIT_NOFILE, &old_lim) == 0) 
        printf("Old limits -> soft limit= %ld \t"
            " hard limit= %ld \n", old_lim.rlim_cur, old_lim.rlim_max); 

    #endif 

    struct rlimit limit; 
    limit.rlim_cur = maxFd; 
    limit.rlim_max = maxFd; 
    if(setrlimit(RLIMIT_NOFILE, &limit) == -1){
        throw runtime_error(PROC_LIMIT_FAIL); 
    }

    #ifdef DEBUG
    struct rlimit new_lim; 
    if( getrlimit(RLIMIT_NOFILE, &new_lim) == 0) 
        printf("New limits -> soft limit= %ld "
         "\t hard limit= %ld \n", new_lim.rlim_cur,  
                                  new_lim.rlim_max);
    #endif 


    return true; 
}

bool setLimitProcCount(int maxProc){

    #ifdef DEBUG
    struct rlimit old_lim; 
    if( getrlimit(RLIMIT_NPROC, &old_lim) == 0) 
        printf("Old limits -> soft limit= %ld \t"
            " hard limit= %ld \n", old_lim.rlim_cur, old_lim.rlim_max); 

    #endif

    struct rlimit limit; 
    limit.rlim_cur = maxProc; 
    limit.rlim_max = maxProc; 
    if(setrlimit(RLIMIT_NPROC, &limit) == -1){
        throw runtime_error(PROC_LIMIT_FAIL); 
    }

    #ifdef DEBUG
    struct rlimit new_lim; 
    if( getrlimit(RLIMIT_NPROC, &new_lim) == 0) 
        printf("New limits -> soft limit= %ld "
         "\t hard limit= %ld \n", new_lim.rlim_cur,  
                                  new_lim.rlim_max);
    #endif 


    return true; 
}


bool setLimitMemory(int maxMemory){
    unsigned int byteMemory = static_cast<unsigned int>(maxMemory) * 1000'000; 
    #ifdef DEBUG
    struct rlimit old_lim; 
    if( getrlimit(RLIMIT_AS, &old_lim) == 0) 
        printf("Old limits -> soft limit= %ld \t"
            " hard limit= %ld \n", old_lim.rlim_cur, old_lim.rlim_max); 

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
    if( getrlimit(RLIMIT_AS, &new_lim) == 0) 
        printf("New limits -> soft limit= %ld "
         "\t hard limit= %ld \n", new_lim.rlim_cur,  
                                  new_lim.rlim_max);
    #endif 

    return true; 
}