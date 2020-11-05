#ifndef __EXEBOX_H__
#define __EXEBOX_H__

#include "../IO/ProblemInfo.hpp"
#include "../system/error.hpp"
#include "../system/config.hpp"
#include "childproc.hpp"

#include "IBaseLang.hpp"
#include "../lang/C.hpp"
#include "../lang/CPP.hpp"
#include "../lang/PYTHON_2.hpp"
#include "../lang/PYTHON_3.hpp"

#include <fstream> 
#include <iostream> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <fcntl.h> 

#include <sys/time.h> 
#include <sys/resource.h>

enum ExeResult {MEM_LIM_EXCEED, TIME_LIM_EXCEED, RUNT_ERR, JUDGE_ERR, GOOD}; 

class ExecuteBox{
private: 
    ProblemInfo pinfo;  //problme info 
    IBaseLang* lang;    //ibaseLang 
    ExeResult getExecuteResult(int status); 
public:
    ExecuteBox(ProblemInfo _p)
    :pinfo(_p){
        Lang l = pinfo.getLang(); 
        if(l == PYTHON3){
            lang = new PYTHON_3; 
        }
        else if(l == PYTHON2){
            lang = new PYTHON_2; 
        }
        else if(l == CPP11){
            lang = new CPP(11); 
        }
        else if(l == CPP14){
            lang = new CPP(14); 
        }
        else if(l == CPP17){
            lang = new CPP(17); 
        }
        else if(l== C99){
            lang = new C(99); 
        }
        else if(l== C11){
            lang = new C(11); 
        }
        else{ //default
            throw logic_error("invalid language selection in executeBox"); 
        }
    }
    bool compile(char* compileMsg, int msgSize);
    ExeResult executeTC(int testCaseNo);
};

#endif