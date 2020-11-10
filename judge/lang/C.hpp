#ifndef __C__H_
#define __C__H_

#include "../core/IBaseLang.hpp"
#include <stdexcept> 

class C : public IBaseLang{
private:
    bool processCtrl = true; 
    const string compiler = "/usr/bin/gcc"; 
    vector<string> compileArgs = {
        "-o", "main",
        "-O2", 
        "-lm",
        "-Wall",
    //    "-static",
        "Main.c"
    };
    vector<string> compileEnvs = {}; 

    const string executor = "./main"; 
    vector<string> executeArgs = {}; 
    vector<string> executeEnvs = {}; 

    vector<int> syscallList = {}; 

public: 
    C(int version){
        if(version == 11){
            compileArgs.push_back("-std=gnu11"); 
        }
        else if(version == 99){
            compileArgs.push_back("-std=gnu99"); 
        }
        else{
            throw logic_error("invalid version for gcc, only 11, 99 is possible"); 
        }
    }
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