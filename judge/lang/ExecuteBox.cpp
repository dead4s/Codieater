#include "ExecuteBox.hpp"


void ExecuteBox::getReadyArgs(vector<char*>& readyArgs){
    cout << "getReadyArgs" << endl; 
    const vector<string>& langArgs = lang.getArgs();
    string compiler = lang.getCompiler(); 

    string inputCode = MARKPATH + pinfo.getMarkNo() + "/" + lang.getFname();  
    readyArgs.push_back(const_cast<char*>(compiler.c_str())); 
 
    cout << "inputCode : " << inputCode << endl; 
    cout <<"compiler : " << compiler.c_str() << endl; 
    for(int i = 0; i < langArgs.size(); i++){
        readyArgs.push_back(const_cast<char*>(langArgs[i].c_str())); 
        cout << langArgs[i] << endl; 
    }
    readyArgs.push_back(const_cast<char*>(inputCode.c_str()));
    readyArgs.push_back(nullptr); 
    return; 
}


bool ExecuteBox::compile(){
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
    if(pid > 0){
        //parent process
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
            //TODO : write to result.json 
            dup2(1, pipeFile[0]); 
            fflush(stdout); 
            close(pipeFile[0]); 
            close(pipeFile[1]); 

           if(compileResult == 0){
                cout << "compile success " << endl; 
            }
            else{
                cout << "compile Result : " << compileResult << endl; 
                cout << "compile error " << endl; 
            }
            return bool(compileResult); 
        }
        else{
            throw runtime_error(addTag(PROC_CHILD_RET_UNKOWN, f)); 
        }
    }
    else{
        //dup2(pipeFile[1], 1); 
        //dup2(pipeFile[1], 2); 

        vector<char*> readyArgs; 
        getReadyArgs(readyArgs); 
        const char* path = lang.getCompiler().c_str(); 
        char** args = readyArgs.data(); 

        cout << readyArgs.size() << endl; 
        for(int i = 0; i < readyArgs.size(); i++){
            cout << string(readyArgs[i]) << endl; 
        }

        execv(path, &(args[0])); 
        cerr << strerror(errno) << endl; 
        _exit(-1); 
    }
    return 0; 
}