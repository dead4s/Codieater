#ifndef __TCRES__H_
#define __TCRES__H_

#include <iostream> 
#include <fstream> 
#include <vector> 
#include <sstream>
#include <iomanip>
#include <string>
#include "../core/ExeResult.hpp"

using namespace std; 

class TestCaseResult{
friend ostream& operator<< (ostream& os, const TestCaseResult& tcRes); 
private : 
    ExeResult result; 
    bool check; 
public:
    int time;
    int CPUtime;  
    int memory;
    TestCaseResult(); 
    stringstream seq2json(string space = "\t") const; 
    void setResult(const ExeResult e); 
    bool getCheck() const; 
}; 

#endif