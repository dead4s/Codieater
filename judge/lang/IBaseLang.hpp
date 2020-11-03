#ifndef __IBASE__H_
#define __IBASE__H_

#include <string> 
#include <vector>
using namespace std; 

//language interface
class IBaseLang{
public:
    virtual const string& getCompiler() = 0; 
    virtual const vector<string>& getArgs() = 0; 
    virtual const vector<string>& getEnv() = 0; 
}; 

#endif