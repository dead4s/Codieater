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
    vector<int> syscallList = {}; 
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
        executeArgs.insert(executeArgs.begin(), "-Xmx"+to_string(memory) + "m"); 
        executeArgs.insert(executeArgs.begin(), "-Xss"+to_string(memory) + "m"); 
    } 


    virtual const vector<string>& getExecuteArgs(){
        return executeArgs;  
    }

    virtual const vector<string>& getExecuteEnvs(){
        return executeEnvs; 
    }

    virtual const ExeResult checkExeResultValue(int exitCode){
        //https://docs.oracle.com/javase/8/docs/technotes/tools/windows/java.html
        if(exitCode == 0)
            return GOOD; 
        if(exitCode == 1)
            return MEM_LIM_EXCEED; 
        return RUNT_ERR; 
    }

    virtual vector<int> getMoreSysList(){
        return syscallList; 
    }
}; 
#endif