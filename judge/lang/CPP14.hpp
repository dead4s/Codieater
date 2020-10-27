#ifndef __CPP14__H_
#define __CPP14__H_

#include "IBaseLang.hpp"

class CPP14{
public: 
    virtual string syntaxCheck(string submitCode){
        return "g++" + submitCode + "-o Main -O2 -Wall -lm -static -std=gnu++14 -DONLINE_JUDGE"; 
    }
}; 

#endif