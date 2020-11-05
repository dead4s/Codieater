#include "ExecuteBox.hpp"

ExeResult ExecuteBox::getExecuteResult(int status){
    if(WIFSIGNALED(status)){
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
    else if(WIFEXITED(status)){
        int tcResult = WEXITSTATUS(status); 
        if(tcResult == 0){
                return GOOD; 
        }
        else{
            return RUNT_ERR; 
        }
    }
    else{
        throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN)); 
    }
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
        else if(WIFSIGNALED(status)){
            cerr << strerror(errno) <<  endl; 
            throw runtime_error(addTag(PROC_CHILD_KILLED, f)); 
        }
        else if(WIFEXITED(status)){
            int compileResult = WEXITSTATUS(status); 
            memset(compileMsg, '\0', msgSize); 
            read(pipeFile[0], compileMsg, msgSize); 
            close(pipeFile[0]); 
            close(pipeFile[1]); 
            return !bool(compileResult); 
        }
        else{
            throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN, f)); 
        }
    }
    else{ //child process
        dup2(pipeFile[1], STDOUT_FILENO); //stdout -> pipeFile[1]
        dup2(pipeFile[1], STDERR_FILENO);  //stderr -> pipeFile[0]

        string path = MARKPATH; 
        string cmd = lang->getCompiler(); 
        vector<string> arg = lang->getCompileArgs(); 
        vector<string> env = lang->getCompileEnvs(); 
        startChildProc(path, cmd, arg, env); 
    }  
    return 0; 
}

ExeResult ExecuteBox::executeTC(int testCaseNo, int& memUsed){
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
        while(1){
            waitPid = wait3(&status, 0, &usedResource); 
            if(waitPid == -1 && errno == EINTR)
                continue; 
            break; 
        }
        memUsed =  usedResource.ru_maxrss; 
        //while( ((waitPid = wait(&status)) == -1) && errno == EINTR); 
 
        if(waitPid == -1){
            throw runtime_error(addTag(PROC_CHILD_RET_ERROR, f)); 
        }
        return getExecuteResult(status); 
    }
    else{//child process
        
        string inputFile = PROBPATH +"/in/" + to_string(testCaseNo) +".in"; 
        string outputFile = MARKPATH + "/" +  to_string(testCaseNo) + ".out"; 

        #ifndef DEBUG
        int inputFd = open(inputFile.c_str(), O_RDONLY); 
        int outputFd = open(outputFile.c_str(), O_CREAT| O_WRONLY | O_TRUNC, 0666); 
        dup2(inputFd, STDIN_FILENO); 
        dup2(outputFd, STDOUT_FILENO); 
        close(inputFd); 
        close(outputFd); 
        #endif 

        // setLimitFd(100);
        setLimitProcCount(1);
        setLimitMemory(pinfo.getMemory());

        /*TODO
            writing to file might bring overhead
            i'd like to use BUFFER
            ->  but dup2 need file descripter (C style)
                and for buffer in memory i can't get file descripter 
            ->  set sstream reidirect with ostream (C++ style)
                i'm not sure about inner implementation of ostream
                but this is not working8
        */ 
       
        string path = MARKPATH; 
        string prog = lang->getExecutor();
        vector<string> arg = lang->getExecuteArgs(); 
        vector<string> env = lang->getExecuteEnvs();
        startChildProc(path, prog, arg, env); 
    }
    return JUDGE_ERR; 
}
