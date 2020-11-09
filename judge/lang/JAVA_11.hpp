#ifndef __JAVA__H_
#define __JAVA__H_

#include "../core/IBaseLang.hpp"

class JAVA_11 : public IBaseLang{
private:
    bool processCtrl = false; 
    const string compiler = "/usr/bin/javac"; 
    vector<string> compileArgs = {
        "Main.java"
    };
    vector<string> compileEnvs = {}; 


    const string executor = "/usr/bin/java"; 
    vector<string> executeArgs = {
        "Main"
    }; 
    vector<string> executeEnvs = {}; 

public: 
    JAVA_11(){}

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

    virtual const void addDynamicExecuteArgs(int memory){
        executeArgs.push_back("-Xmx"+to_string(memory) + "m"); 
    } 


    virtual const vector<string>& getExecuteArgs(){
        return executeArgs;  
    }

    virtual const vector<string>& getExecuteEnvs(){
        return executeEnvs; 
    }

}; 
#endif