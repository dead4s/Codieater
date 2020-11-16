#include "TestCaseResult.hpp"


TestCaseResult::TestCaseResult(){};


string RE2Str(enum ExeResult res){
   switch (res) 
   {
        case MEM_LIM_EXCEED: return "memory limit exceeded";
        case TIME_LIM_EXCEED : return "time limit execeeded"; 
        case RUNT_ERR : return "runtime error";
        case JUDGE_ERR  : return "judge inside error";
        case GOOD : return "execution sccuess"; 
        case CORRECT : return "correct"; 
        case WRONG : return "wrong answer"; 
   }
   return "invalid";
}

ostream& operator<< (ostream& os, const TestCaseResult& tcRes){
    os << "check \t\t" << tcRes.check << endl; 
    os << "message \t\t" << RE2Str(tcRes.result) << endl; 
    return os; 
}


void TestCaseResult::setResult(const ExeResult e){
    if(e == GOOD || e == CORRECT)
        check = true; 
    else
        check = false; 
    result = e; 
    return; 
}


bool TestCaseResult::getCheck() const{
    return check; 
} 


stringstream TestCaseResult::seq2json(string space) const{
    stringstream jsonForm; 
    jsonForm << space << "{" << endl;

    if(check == true){
        jsonForm << space << "\"memory\" : "  << memory << "," << endl; 
        jsonForm << space << "\"time\" : " << time << "," << endl; 
        jsonForm << space << "\"CPUtime\" : " << CPUtime <<"," << endl; 
    }
    jsonForm << space << "\"check\" : " << check << "," << endl; 
    jsonForm << space << "\"msg\" : \"" << RE2Str(result)<< "\"" << endl; 
    jsonForm << space << "}"; 
    return jsonForm; 
}