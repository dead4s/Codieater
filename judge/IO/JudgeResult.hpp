#ifndef __JUDGERES__H_
#define __JUDGERES__H_

#include <iostream> 
#include <fstream> 
#include <vector> 
#include <sstream>
#include <iomanip>
#include <string>
#include "TestCaseResult.hpp"

using namespace std; 

class JudgeResult{
friend ostream& operator<< (ostream& os, const JudgeResult& res); 
public: 
    bool compileResult; 
    string compileMessage; 
    vector<TestCaseResult> tcResults; 
    JudgeResult(){}
    stringstream seq2json(string space = "\t"); 
}; 

#endif