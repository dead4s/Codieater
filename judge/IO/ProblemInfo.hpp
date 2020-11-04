#ifndef __PROINFO_H__
#define __PROINFO_H__


#include <string>
#include <iostream> 
#include <cstring>
#include "languageType.hpp"

using namespace std; 

class ProblemInfo{
friend ostream& operator << (ostream& os, const ProblemInfo& info);

private:
    const int _time; 
    const int _memory; 
    const Lang _lang; 
    const string _markNo; 
    const string _probNo; 

public: 
    ProblemInfo();
    ProblemInfo(int t, int m, Lang l, string code, string data);
    ProblemInfo(const ProblemInfo& p); 
    int getTime(){
        return _time; 
    }
    int getMemory(){
        return _memory; 
    }
    Lang getLang(){
        return _lang; 
    }
    string getMarkNo(){
        return _markNo; 
    }
    string getProbNo(){
        return _probNo; 
    }
}; 



#endif