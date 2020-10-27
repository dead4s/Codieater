#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
using namespace std; 

//language interface
class IBaseLang{
public:
    virtual string syntaxCheck() = 0; 
    virtual string execute() = 0;
}; 

#endif