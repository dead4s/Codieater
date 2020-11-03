#ifndef __PROINFO_H__
#define __PROINFO_H__


#include <string>
#include <iostream> 
#include <cstring>

using namespace std; 


enum Lang {CPP11, CPP14, CPP17, PYTHON2, PYTHON3, C11, C99, INVALID}; 

Lang str2Lang(char* str);

const char* lang2Str(enum Lang l);


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