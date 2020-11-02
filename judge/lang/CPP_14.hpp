#ifndef __CPP14__H_
#define __CPP14__H_

#include "IBaseLang.hpp"

class CPP_14{
private:
    static vector<string> saveArg; 
    static vector<string> saveEnv; 
    static const string compiler; 
    static const string srcFile;

public: 
    static const string& getCompiler(){
        return compiler; 
    }

    static const vector<string>& getArgs(){
        return saveArg; 
    }

    static const vector<string>& getEnv(){
        return saveEnv; 
    }

    static const string& getFname(){
        return srcFile; 
    }
}; 
#endif