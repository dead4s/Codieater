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
    ProblemInfo(int t, int m, Lang l);
    ProblemInfo(const ProblemInfo& p); 
    const int getTime() const {
        return _time; 
    }
    const int getMemory() const {
        return _memory; 
    }
    const Lang getLang() const {
        return _lang; 
    }

private:
    const int _time; 
    const int _memory; 
    const Lang _lang; 
}; 

#endif