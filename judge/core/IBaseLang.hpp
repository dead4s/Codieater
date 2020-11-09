#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
#include <vector>
using namespace std; 

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
}; 

#endif