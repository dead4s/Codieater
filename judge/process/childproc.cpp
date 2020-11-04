#include "childproc.hpp"

int startChildProc(string path, string cmd, vector<string> args, vector<string> env){
    const char* cpath = path.c_str(); 
    const char* ccmd = cmd.c_str(); 
    
    /*
    cout << endl; 
    cout << path << endl; 
    cout << cmd << endl; 
    for(int i = 0; i < args.size(); i++){
        cout << args[i] << " "; 
    }
    */

    chdir(cpath); 
    vector<char*> cargs;
    cargs.push_back(const_cast<char*>(ccmd)); 
    for(int i = 0; i < args.size(); i++){
        cargs.push_back(const_cast<char*>(args[i].c_str())); 
    }
    cargs.push_back(nullptr); 
    char** readyArgs = cargs.data(); 
    //TODO - need to add for env setting 
    execvp(ccmd, &(readyArgs[0])); 
    cerr << strerror(errno) << endl; 
    return -1; 
}
