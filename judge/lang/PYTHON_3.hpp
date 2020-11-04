#ifndef __PYTHON3__H_
#define __PYTHON3__H_

#include "IBaseLang.hpp"

class PYTHON_3 : public IBaseLang{
private : 
private : 
    const string compiler = "/usr/bin/python3"; 
    vector<string> compileArgs = {
        "-m", "py_compile", 
        "Main.py"
    };
    vector<string> compileEnvs = {}; 

    const string executor = "/usr/bin/python3"; 
    vector<string> executeArgs = {"Main.py"}; 
    vector<string> executeEnvs = {}; 

public: 
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
}; 

#endif