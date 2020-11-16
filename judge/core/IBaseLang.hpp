#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
#include <vector>
#include <map>
#include <algorithm> 
#include <cstdarg> 
#include "Seccomp.hpp"
#include "ExeResult.hpp"
using namespace std; 

//language interface
class IBaseLang{
public:
    //options for compilation
    virtual const string& getCompiler() = 0; 
    virtual const void addDynamicCompileArgs(const ProblemInfo& p){};
    virtual const vector<string>& getCompileArgs() = 0; 
    virtual const vector<string>& getCompileEnvs() = 0; 

    //options for execution 
    virtual const string& getExecutor() = 0; 
    virtual const void addDynamicExecuteArgs(const ProblemInfo& p){}; 
    virtual const vector<string>& getExecuteArgs() = 0; 
    virtual const vector<string>& getExecuteEnvs() = 0; 

    //check return value, you can override to user languages
    virtual const ExeResult checkExeResultValue(int exitCode){
        if(exitCode == 0)
            return GOOD; 
        return RUNT_ERR; 
    }

    virtual const ExeResult checkErrorMsg(char* msg){
        return UNDEFINED; 
    }
    //use process control or not
    virtual const bool getProcCtrl() = 0;
    
    //get syscall white/black list by languages
    virtual vector<int> getMoreSysList() = 0; 
}; 

#endif