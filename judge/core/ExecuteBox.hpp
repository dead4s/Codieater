#ifndef __EXEBOX_H__
#define __EXEBOX_H__

#include "../IO/ProblemInfo.hpp"
#include "../IO/TestCaseResult.hpp"
#include "../system/error.hpp"
#include "../system/config.hpp"
#include "ExeResult.hpp"
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


class ExecuteBox{
public:
    ExecuteBox(ProblemInfo _p); 
    bool compile(char* compileMsg, int msgSize);
    TestCaseResult executeTC(int testCaseNo);
private: 
    ProblemInfo pinfo;
    IBaseLang* lang;
    ExeResult parseSignalValue(int status); 
    ExeResult parseExitValue(int exitCode); 
};

#endif