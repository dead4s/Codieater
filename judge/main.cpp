#include <iostream>
#include <string> 
#include <unistd.h>
#include <stdexcept> 
#include "util/ProblemInfo.hpp"

using namespace std; 

static void showUsage(string programName){
    cerr << "Usage: " << programName << "options sources" 
        << "Options : \n" 
        << "\t-h --help\t\tShow this help message\n"
        << "\t-t --time\t\t(Optional)Set execution time Limit in ms, default value = 2000ms\n"
        << "\t-m --memory\t\t(Optional)Set max memory Limit in MB, default value = 512MB\n"
        << "\t-l --lang\t\tSet judge Language\n"
        << "\t-c --code\t\tSet code file Name and Directory, usually in /home/input/code/{codefile}\n"
        << "\t-d --data\t\tSet data files Directory, usually in /home/input/data/[1-9]*'.'(in|out)?\n";
    return;  
}

static bool checkAllArg(Lang l, string code, string data){
    if(l == INVALID){
        cerr <<"you must select language type with -l option" << endl; 
        return false; 
    }
    if(code.empty()){
        cerr <<"you must give code directory with -c option" << endl; 
        return false; 
    }
    if(data.empty()){
        cerr <<"you must give data directory with -d option" << endl; 
        return false; 
    }
    return true; 
}

int main(int argc, char* argv[]){
    int time = 2000; //default value
    int memory = 512; //default value
    Lang lang = INVALID;
    string codeDir; 
    string dataDir;

    char option; 
    const char* optstring = "t:m:l:c:d:h"; 
    optind = 1; 
    while(-1 != (option = getopt(argc, argv, optstring)) ){
        switch(option){
            case 'h':
                showUsage(argv[0]); 
                exit(0); 
            case 't':
                time = atoi(optarg); 
                break; 
            case 'm':
                memory = atoi(optarg); 
                break; 
            case 'l':
                lang = str2Lang(optarg); 
                break; 
            case 'c':
                codeDir = string(optarg); 
                break; 
            case 'd':
                dataDir = string(optarg); 
                break; 
            default: 
                throw invalid_argument("unknown option" + string(argv[optind-1])); 
        }
    }
    checkAllArg(lang, codeDir, dataDir); 
    ProblemInfo pinfo(time, memory, lang, codeDir, dataDir);
    cout << pinfo << endl;  
    return 0;
}