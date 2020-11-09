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
#include "../lang/JAVA_11.hpp"

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
public:
    ExecuteBox(ProblemInfo _p); 
    bool compile(char* compileMsg, int msgSize);
    ExeResult executeTC(int testCaseNo, int& memUsed, int& timeUsed);
private: 
    ProblemInfo pinfo;
    IBaseLang* lang;
    ExeResult getExecuteResult(int status); 
};

#endif