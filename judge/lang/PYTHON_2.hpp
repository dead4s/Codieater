#ifndef __PYTHON2__H_
#define __PYTHON2__H_

#include "../core/IBaseLang.hpp"

class PYTHON_2 : public IBaseLang{
private : 
    bool processCtrl = true; 

    const string compiler = "/usr/bin/python2"; 
    vector<string> compileArgs = {
        "-m", "py_compile", 
        "Main.py"
    };
    vector<string> compileEnvs = {}; 

    const string executor = "/usr/bin/python2"; 
    vector<string> executeArgs = {"Main.py"}; 
    vector<string> executeEnvs = {

    }; 

    vector<int> syscallList = {};  

public: 
    virtual const bool getProcCtrlFlag(){
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
}; 

#endif