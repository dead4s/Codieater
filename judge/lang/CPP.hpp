#ifndef __CPP__H_
#define __CPP__H_

#include "IBaseLang.hpp"

class CPP : public IBaseLang{
private:
    vector<string> saveArg = {
        "-o", "main",
        "-O2", 
        "-lm",
        "-Wall",
        "-static",
        "Main.cpp"
    };
    vector<string> saveEnv = {
    }; 
    const string compiler = "/usr/bin/g++"; 
public: 
    CPP(int version){
        if(version == 11){
            saveArg.push_back("-std=gnu++11"); 
        }
        else if(version == 14){
            saveArg.push_back("-std=gnu++14"); 
        }
        else if(version ==17){
            saveArg.push_back("-std=gnu++17"); 
        }
        else{
            throw logic_error("invalid version for g++ , only 11, 14, 17 is possible");
        }
    }
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