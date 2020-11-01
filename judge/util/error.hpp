#ifndef __ERROR_H_
#define __ERROR_H_

#include <string> 
using namespace std; 

string inline addTag(const string err, const string func = ""){
    if(func == ""){
        return err; 
    }
    return func + "::" + err; 
}

const string PROC_PIPE_CREATE_FAIL = "Process Pipe create failed";

const string PROC_FORK_FAIL = "fork to create subprocess Failed, PID is negative"; 

const string PROC_CHILD_RET_ERROR = "child process have some problem";

const string PROC_CHILD_KILLED = "child process is killed by sginal"; 

const string PROC_CHILD_RET_UNKOWN = "child process have some problem but not specified in the code"; 

const string PROC_EXEC_ERROR = "Exec failed so cannot switch to child's new image"; 
#endif 

/*
#ifdef DEBUG
const std:string SOME_ERROR = "More detailed error information for developers"
#else
const std:string SOME_ERROR = "Human friendly error message"
#endif
*/