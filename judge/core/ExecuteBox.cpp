#include "ExecuteBox.hpp"

ExecuteBox::ExecuteBox(ProblemInfo _p)
: pinfo(_p)
{
    Lang langSelect = pinfo.getLang();
    switch (langSelect)
    {
    case PYTHON2:
        lang = new PYTHON_2; 
        break;
    case PYTHON3: 
        lang = new PYTHON_3; 
        break; 
    case CPP11:
        lang = new CPP(11); 
        break; 
    case CPP14: 
        lang = new CPP(14); 
        break; 
    case CPP17:
        lang = new CPP(17); 
        break; 
    case C99:
        lang = new C(99); 
        break; 
    case C11: 
        lang = new C(11); 
        break; 
    case JAVA11: 
        lang = new JAVA_11; 
        break; 
    default:
        throw logic_error("invalid Language selection in execute box constructor"); 
        break;
    }
}


ExeResult ExecuteBox::parseSignalValue(int status){
    cerr << "signal number is " <<  WTERMSIG(status) << endl; 
    if(WTERMSIG(status) == SIGKILL){
        return TIME_LIM_EXCEED; 
    }
    if(errno == ENOMEM){ //memory limit fail 
        cerr << strerror(errno) << endl; 
        cerr << "ENOMEM  => memory limit exceeded " << endl; 
        return MEM_LIM_EXCEED; 
    }
    if(errno == EAGAIN){
        cerr << strerror(errno) <<  endl; 
        cerr << "EAGAIN => fail to create child, it seems like memory time limit" << endl; 
        return MEM_LIM_EXCEED; 
    }
    cerr << errno << endl; 
    cerr << strerror(errno) <<  endl; 
    cerr << "uncatched signal.." << endl; 
    return RUNT_ERR; 
}


ExeResult ExecuteBox::parseExitValue(int exitCode){
    return lang->checkExeResultValue(exitCode); 
}


bool ExecuteBox::compile(char* compileMsg, int msgSize){
    string f =  "compile"; 

    int pipeFile[2]; 
    int status; 

    if(pipe(pipeFile) == - 1){
        throw runtime_error(addTag(PROC_PIPE_CREATE_FAIL, f)); 
    }
    //make sure that pipe is non blocking
    //if not, read function can stuck 
    if (fcntl(pipeFile[0], F_SETFL, O_NONBLOCK) < 0) 
        exit(2); 

    pid_t pid; 
    pid = fork(); 
    if(pid < 0){
        throw runtime_error(addTag(PROC_FORK_FAIL, f)); 
    }
    if(pid > 0){ //parent process 
        pid_t waitPid; 
        while( ((waitPid = wait(&status)) == -1) && errno == EINTR); 
        if(waitPid == -1){
            throw runtime_error(addTag(PROC_CHILD_RET_ERROR, f)); 
        }
        if(WIFSIGNALED(status)){
            cerr << strerror(errno) <<  endl; 
            cerr << "compile Routine Failed - stopped by signals" << endl; 
            return false; 
        }
        if(WIFEXITED(status)){
            int compileResult = WEXITSTATUS(status); 
            memset(compileMsg, '\0', msgSize); 
            read(pipeFile[0], compileMsg, msgSize); 
            close(pipeFile[0]); 
            close(pipeFile[1]); 
            return !bool(compileResult); 
        }
        throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN, f)); 
    }
    else{ //child process
        redirectFd(pipeFile[1], STDOUT_FILENO, false); 
        redirectFd(pipeFile[1], STDERR_FILENO, true); 
        close(pipeFile[0]); 

        string path = MARKPATH; 
        string cmd = lang->getCompiler(); 
        vector<string> arg = lang->getCompileArgs(); 
        vector<string> env = lang->getCompileEnvs(); 
        startChildProc(path, cmd, arg, env); 
    }  
    return 0; 
}


int openFile(string fileName, int flag, int perm){
    int fd = open(fileName.c_str(), flag, perm); 
    if(fd < 0)
        throw runtime_error("fail to open " + fileName);
    return fd;   
}


ExeResult ExecuteBox::executeTC(int testCaseNo, int& memUsed, int& timeUsed){
    string f = "executeTC"; 
    pid_t pid; 
    int status; 

    pid = fork(); 
    if(pid < 0){
        throw runtime_error(addTag(PROC_FORK_FAIL, f)); 
    }
    if(pid> 0){ //parent process
        pid_t waitPid; 
        struct rusage usedResource; 
        setLimitTime(pinfo.getTime(), pid); 
        while(1){
            waitPid = wait3(&status, 0, &usedResource); 
            if(waitPid == -1 && errno == EINTR)
                continue; 
            break; 
        }
        removeLimitTime(); 
        if(waitPid == -1)
            throw runtime_error(addTag(PROC_CHILD_RET_ERROR, f)); 

        memUsed = getUsedMemory(usedResource); 
        timeUsed = getUsedCPUTime(usedResource); 

        if(WIFSIGNALED(status))
            return parseSignalValue(status);
        if(WIFEXITED(status))
            return parseExitValue(WEXITSTATUS(status)); 
        throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN)); 

    }
    else{//child process
        int inputFd = openFile(PROBPATH +"/in/" + to_string(testCaseNo) +".in", O_RDONLY, 0666); 
        redirectFd(inputFd, STDIN_FILENO, true);         
        int outputFd = openFile(MARKPATH + "/" +  to_string(testCaseNo) + ".out", O_CREAT| O_WRONLY | O_TRUNC, 0666); 
        redirectFd(outputFd, STDOUT_FILENO, true); 

        //use process control 
        if(lang->getProcCtrlFlag() == true){
            setLimitProcCount(1); 
            setLimitMemory(pinfo.getMemory());
        }
        else{//use language own control
            lang->addDynamicExecuteArgs(pinfo.getMemory()); 
        }
        /*TODO
            writing to file might bring overhead :: i'd like to use BUFFER
            ->  but dup2 need file descripter (C style)
                and for buffer in memory i can't get file descripter 
            ->  set sstream redirect with ostream (C++ style)
                i'm not sure about inner implementation of ostream
                but i tried but it is not working:(
        */ 
       
        string path = MARKPATH; 
        string prog = lang->getExecutor();
        vector<string> arg = lang->getExecuteArgs(); 
        vector<string> env = lang->getExecuteEnvs();
        startChildProc(path, prog, arg, env); 
    }
    return JUDGE_ERR; 
}
