#ifndef __CPP__H_
#define __CPP__H_

#include "../core/IBaseLang.hpp"

class CPP : public IBaseLang{
private:
    bool processCtrl = true; 
    const string compiler = "/usr/bin/g++"; 
    vector<string> compileArgs = {
        "-o", "main",
        // "-O2", 
        "-lm",
        "-Wall",
        // "-static",
        "Main.cpp"
    };
    vector<string> compileEnvs = {}; 


    const string executor = "./main"; 
    vector<string> executeArgs = {}; 
    vector<string> executeEnvs = {}; 
    vector<int> syscallList = {}; 

public: 
    CPP(int version){
        if(version == 11){
            compileArgs.push_back("-std=gnu++11"); 
        }
        else if(version == 14){
            compileArgs.push_back("-std=gnu++14"); 
        }
        else if(version ==17){
            compileArgs.push_back("-std=gnu++17"); 
        }
        else{
            throw logic_error("invalid version for g++ , only 11, 14, 17 is possible");
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