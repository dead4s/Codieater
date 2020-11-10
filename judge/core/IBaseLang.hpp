#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
#include <vector>
#include <map>
#include <algorithm> 
#include "Seccomp.hpp"
using namespace std; 

enum ExeResult {MEM_LIM_EXCEED, TIME_LIM_EXCEED, RUNT_ERR, JUDGE_ERR, GOOD}; 

//language interface
class IBaseLang{
public:
    virtual const bool getProcCtrlFlag() = 0; 
    virtual const string& getCompiler() = 0; 
    virtual const void addDynamicCompileArgs(int){}
    virtual const vector<string>& getCompileArgs() = 0; 
    virtual const vector<string>& getCompileEnvs() = 0; 

    virtual const string& getExecutor() = 0; 
    virtual const void addDynamicExecuteArgs(int){}
    virtual const vector<string>& getExecuteArgs() = 0; 
    virtual const vector<string>& getExecuteEnvs() = 0; 

    virtual const ExeResult checkExeResultValue(int exitCode){
        if(exitCode == 0)
            return GOOD; 
        return RUNT_ERR; 
    }

    virtual vector<int> getWhiteListSyscall() = 0; 
}; 

#endif