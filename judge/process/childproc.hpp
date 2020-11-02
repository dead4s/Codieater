#ifndef __CHLIDPROC_H_
#define __CHILDPROC_H_

#include <unistd.h> 
#include <string> 
#include <vector> 
#include <cstring> 
#include "../config.hpp"

using namespace std; 
/*  startChildProc  : Wrapper class of execv , start child process in specific paht and args
    path : change dir 
    cmd  : command want to be execute 
    args : argument to pass in string array 
    env  : envirnoment varible to set in child process
*/
int startChildProc(string path, string cmd, vector<string> args, vector<string> env); 

#endif
