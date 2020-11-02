#include "JudgeResult.hpp"

using namespace std; 

ostream& operator<< (ostream& os, const TestCaseResult& tcRes){
    os << "check \t\t" << tcRes.check << endl; 
    os << "message \t\t" << tcRes.check << endl; 
    return os; 
}


ostream& operator<< (ostream& os, const JudgeResult& res){ 
    os << "===== JudgeReulst =====\n" 
    << "compile Reulst \t\t" << res.compileResult << endl
    << "compile Message \t\t" << res.compileMessage << endl; 
    os << "====> Reuslt for TestCase " << endl; 
    for(int i = 0; i < res.tcResults.size(); i++){
        os << "testCase[" << i+1 << "]" << endl; 
        os << res.tcResults[i] << endl; 
    }
    return os; 
}