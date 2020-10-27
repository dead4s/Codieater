#ifndef __EXEBOX_H__
#define __EXEBOX_H__

#include "util/ProblemInfo.hpp"
#include "IBaseLang.hpp"
#include <fstream> 
#include <iostream> 

class ExecuteBox{
private: 
    ofstream file;      //result file
    ProblemInfo pinfo;  //problme info 
    IBaseLang* lang;    //ibaseLang  
};

#endif