#ifndef __JUDGERES__H_
#define __JUDGERES__H_

#include <iostream> 
#include <string>
#include <vector> 
using namespace std; 

class TestCaseResult{
friend ostream& operator<< (ostream& os, const TestCaseResult& tcRes); 
public:
    bool check; 
    string msg;  
    TestCaseResult(bool c, string m)
    :check(c), msg(m){}
}; 

class JudgeResult{
friend ostream& operator<< (ostream& os, const JudgeResult& res); 
public: 
    bool compileResult; 
    string compileMessage; 
    vector<TestCaseResult> tcResults; 
    JudgeResult(){}
}; 

#endif