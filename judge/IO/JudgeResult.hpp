#ifndef __JUDGERES__H_
#define __JUDGERES__H_

#include <iostream> 
#include <fstream> 
#include <vector> 
#include <sstream>
#include <iomanip>
#include <string>

using namespace std; 

class TestCaseResult{
friend ostream& operator<< (ostream& os, const TestCaseResult& tcRes); 
public:
    bool check; 
    std::string msg;  
    int time; 
    int memory; 
    TestCaseResult(bool c, string m, int _time, int _memory); 
    TestCaseResult(bool c, string m); 
    bool seq2json(ostream& file, string space = "\t"); 
}; 

class JudgeResult{
friend ostream& operator<< (ostream& os, const JudgeResult& res); 
public: 
    bool compileResult; 
    string compileMessage; 
    vector<TestCaseResult> tcResults; 
    JudgeResult(){}
    bool seq2json(ostream& file, string space = "\t"); 
}; 

#endif