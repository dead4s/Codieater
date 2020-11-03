#ifndef __C__H_
#define __C__H_

#include "IBaseLang.hpp"
#include <stdexcept> 

class C : public IBaseLang{
private:
    vector<string> saveArg = {
        "-o", "main",
        "-O2", 
        "-lm",
        "-Wall",
        "-static",
        "Main.c"
    };
    vector<string> saveEnv = {
    }; 
    const string compiler = "/usr/bin/gcc"; 
public: 
    C(int version){
        if(version == 11){
            saveArg.push_back("-std=gnu11"); 
        }
        else if(version == 99){
            saveArg.push_back("-std=gnu99"); 
        }
        else{
            throw logic_error("invalid version for gcc, only 11, 99 is possible"); 
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