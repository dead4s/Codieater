#ifndef __PYTHON2__H_
#define __PYTHON2__H_

#include "IBaseLang.hpp"

class PYTHON_2 : public IBaseLang{
private : 
    vector<string> saveArg = {
        "-m", "py_compile", 
        "Main.py"
    };
    vector<string> saveEnv = {}; 
    const string compiler = "/usr/bin/python2";  
    const string target = "Main.py";
public: 
    virtual const string& getCompiler(){
        return compiler; 
    }

    virtual const vector<string>& getArgs(){
        return saveArg; 
    }

    virtual const vector<string>& getEnv(){
        return saveEnv; 
    }

    virtual const string& getTarget(){
        return target; 
    }
}; 

#endif