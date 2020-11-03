#include "ExecuteBox.hpp"

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

        string path = MARKPATH + pinfo.getMarkNo(); 
        string cmd = lang->getCompiler(); 
        vector<string> arg = lang->getArgs(); 
        vector<string> env; 
        startChildProc(path, cmd, arg, env); 
    }  
    return 0; 
}

int ExecuteBox::gradeTestCase(int testCaseNo){
    string f = "gradeTestCase"; 
    pid_t pid; 
    int status; 

    pid = fork(); 
    if(pid < 0){
        throw runtime_error(addTag(PROC_FORK_FAIL, f)); 
    }
    if(pid> 0){ //parent process
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
            int tcResult = WEXITSTATUS(status); 
            return !bool(tcResult); 
        }
        else{
            throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN, f)); 
        }
    }
    else{//child process
        string inputFile = PROBPATH + pinfo.getProbNo() +"/in/" + to_string(testCaseNo) +".in"; 
        string outputFile = MARKPATH + pinfo.getProbNo() + "/" +  to_string(testCaseNo) + ".out"; 
        int inputFd = open(inputFile.c_str(), O_RDONLY); 
        int outputFd = open(outputFile.c_str(), O_CREAT| O_WRONLY | O_TRUNC, 0666); 
        dup2(inputFd, STDIN_FILENO); 
        dup2(outputFd, STDOUT_FILENO); 
        close(inputFd); 
        close(outputFd); 

        string path = "."; 
        string prog = MARKPATH + pinfo.getProbNo() + "/" + lang->getTarget();
        vector<string> arg; 
        vector<string> env;
        startChildProc(path, prog, arg, env); 
    }
    return 0; 
}
