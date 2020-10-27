#ifndef __PROINFO_H__
#define __PROINFO_H__


#include <string>
#include <iostream> 
#include <cstring>

using namespace std; 

enum Lang {CPP11, CPP14, CPP17, PYTHON2, PYTHON3, JAVA, INVALID}; 

class ProblemInfo{
friend ostream& operator << (ostream& os, const ProblemInfo& info);

private:
    const int _time; 
    const int _memory; 
    const Lang _lang; 
    const string _codeDir; 
    const string _dataDir; 

public: 
    ProblemInfo(int t, int m, Lang l, string code, string data);


}; 

Lang str2Lang(char* str);
const char* lang2Str(enum Lang l);

#endif