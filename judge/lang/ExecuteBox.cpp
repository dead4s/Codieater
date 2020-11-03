#include "ExecuteBox.hpp"

bool ExecuteBox::compile(char* compileMsg, int msgSize){
    string f =  "compile"; 

    int pipeFile[2]; 
    int status; 

    if(pipe(pipeFile) == - 1){
        throw runtime_error(addTag(PROC_PIPE_CREATE_FAIL, f)); 
    }
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
        dup2(pipeFile[1], 1); //stdout -> pipeFile[1]
        dup2(pipeFile[1], 2);  //stderr -> pipeFile[0]

        string path = MARKPATH + pinfo.getMarkNo(); 
        string cmd = lang->getCompiler(); 
        vector<string> arg = lang->getArgs(); 
        vector<string> env; 
        startChildProc(path, cmd, arg, env); 
    }  
    return 0; 
}