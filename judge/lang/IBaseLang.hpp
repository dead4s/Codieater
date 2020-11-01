#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
#include <vector>
using namespace std; 

const int MAX_ARG_LEN = 20; 

//language interface
class IBaseLang{
public:
    virtual string getCompiler() = 0; 
    virtual string syntaxCheck() = 0; 
    virtual string execute() = 0;
}; 

#endif