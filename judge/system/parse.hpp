#ifndef __PARSE_H__
#define __PARSE_H__

#include "../IO/ProblemInfo.hpp"
#include <unistd.h>


static void showUsage(string programName){
    cerr << "Usage: " << programName << "options sources" 
        << "Options : \n" 
        << "\t-h \t\tShow this help message\n"
        << "\t-t \t\t(Optional)Set execution time Limit in ms, default value = 2000ms\n"
        << "\t-m \t\t(Optional)Set max memory Limit in MB, default value = 512MB\n"
        << "\t-l \t\tSet judge Language\n";
    return;  
}


static bool checkAllArg(Lang l){
    if(l == INVALID){
        cerr <<"you must select language type with -l option" << endl; 
        return false; 
    }
    return true; 
}


ProblemInfo parseInput(int argc, char* argv[]){
    int time = 2000; //default value
    int memory = 512; //default value
    Lang lang = INVALID;

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
            default: 
                throw invalid_argument("unknown option" + string(argv[optind-1])); 
        }
    }
    bool good = checkAllArg(lang); 
    if(!good){
        throw invalid_argument("option is missing : -l is needed"); 
    }
    ProblemInfo pinfo(time, memory, lang);
    return pinfo; 
}

#endif