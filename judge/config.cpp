#include "config.hpp"

string MARKPATH; 
string PROBPATH; 

const int COMPILE_MSG_LENGTH = 2048; 

void setEnv(){
    try{
        MARKPATH = string(getenv("MARKPATH")); 
        PROBPATH = string(getenv("PROBPATH")); 
    }
    catch(exception& e){
        cerr << e.what() << endl; 
        cerr << "environment variable is not setted" << endl; 
        cerr << "you must set environment variable named 'MARKPATH' and 'PROBPATH'" << endl; 
    }
    return; 
}