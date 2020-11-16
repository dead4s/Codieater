#ifndef __PROINFO_H__
#define __PROINFO_H__


#include <string>
#include <iostream> 
#include <cstring>
#include "languageType.hpp"

using namespace std; 

class ProblemInfo{
friend ostream& operator << (ostream& os, const ProblemInfo& info);

public: 
    ProblemInfo();
    ProblemInfo(int t, int m, int s, Lang l);
    ProblemInfo(const ProblemInfo& p); 
    const int getTime() const {
        return _time; 
    }
    const int getHeap() const {
        return _heap; 
    }
    const Lang getLang() const {
        return _lang; 
    }
    const int getStack() const{
        return _stack; 
    }

private:
    const int _time; 
    const int _heap;
    const int _stack;  
    const Lang _lang; 
}; 

#endif