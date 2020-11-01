#ifndef __EXEBOX_H__
#define __EXEBOX_H__

#include "../util/ProblemInfo.hpp"
#include "../util/error.hpp"
#include "../config.hpp"
//#include "IBaseLang.hpp"
#include "CPP_14.hpp"

#include <fstream> 
#include <iostream> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

class ExecuteBox{
private: 
    ofstream file;      //result file
    ProblemInfo pinfo;  //problme info 
    //IBaseLang* lang;    //ibaseLang 
    CPP_14 lang;  
    void getReadyArgs(vector<char*>& readyArgs); 

public:
    ExecuteBox(ProblemInfo _p)
    :pinfo(_p){}
    bool compile();
};

#endif