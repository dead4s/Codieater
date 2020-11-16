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

    virtual const bool getProcCtrl(){
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
    
    virtual const void addDynamicExecuteArgs(const ProblemInfo& p){ 
        int heap = p.getHeap(); 
        int stack = p.getStack(); 
        executeArgs.insert(executeArgs.begin(), "-Xmx"+to_string(heap) + "m"); 
        executeArgs.insert(executeArgs.begin(), "-Xss"+to_string(stack) + "m"); 
        return; 
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

    virtual const ExeResult checkErrorMsg(char* msg){
        string errorStr(msg);

        size_t found = errorStr.find("java.lang.OutOfMemoryError", 0); 
        if(found != string::npos)
            return MEM_LIM_EXCEED; 
        else
            return UNDEFINED; 
    }
}; 
#endif