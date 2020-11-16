#ifndef __PYTHON3__H_
#define __PYTHON3__H_

#include "../core/IBaseLang.hpp"

class PYTHON_3 : public IBaseLang{
private : 
    bool processCtrl = true; 
    const string compiler = "/usr/bin/python3"; 
    vector<string> compileArgs = {
        "-m", "py_compile", 
        "Main.py"
    };
    vector<string> compileEnvs = {}; 

    const string executor = "/usr/bin/python3"; 
    vector<string> executeArgs = {"Main.py"}; 
    vector<string> executeEnvs = {}; 

    vector<int> syscallList = {
    }; 

public: 
    virtual const bool getProcCtrl(){
        return processCtrl; 
    }
    
    virtual const string& getCompiler(){
        return compiler; 
    }

    virtual const vector<string>& getCompileArgs(){
        return compileArgs; 
    }

    virtual const vector<string>& getCompileEnvs(){
        return compileEnvs; 
    }

    virtual const string& getExecutor(){
        return executor; 
    }

    virtual const vector<string>& getExecuteArgs(){
        return executeArgs;  
    }

    virtual const vector<string>& getExecuteEnvs(){
        return executeEnvs; 
    }
    
    virtual vector<int> getMoreSysList(){
        return syscallList; 
    }

    virtual const ExeResult checkErrorMsg(char* msg){
        string errorStr(msg);

        size_t found = errorStr.find("MemoryError", 0); 
        if(found != string::npos)
            return MEM_LIM_EXCEED; 
        else
            return UNDEFINED; 
    }
}; 

#endif