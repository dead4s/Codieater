#ifndef __CPP14__H_
#define __CPP14__H_

#include "IBaseLang.hpp"

class CPP_14 : public IBaseLang{
private:
    vector<string> saveArg = {
        "-o", "main",
        "-O2", 
        "-lm",
        "-Wall",
        "-static",
        "-std=gnu++14",     
        "Main.cpp"
    };
    vector<string> saveEnv = {
    }; 
    const string compiler = "/usr/bin/g++"; 

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
}; 
#endif