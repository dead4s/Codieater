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
    int heap = 512; //default value
    int stack = 1; //default value
    Lang lang = INVALID;

    char option; 
    const char* optstring = "t:m:s:l:c:d:h"; 
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
                heap = atoi(optarg); 
                break; 
            case 's' : 
                stack = atoi(optarg); 
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
    cout <<"good1" << endl; 
    ProblemInfo pinfo(time, heap, stack, lang);
    return pinfo; 
}

#endif