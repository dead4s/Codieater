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

bool JudgeResult::seq2json(ofstream& file, string space){
    file << "{" << endl;
    file << space << "\"compile\" : " << "\"" << compileResult << "\" ," << endl; 
    file << space << "\"compile_msg\" : " << "\"" << compileMessage << "\" ," << endl; 
    file << space << "\"result\" : ["; 
    for(int i = 0; i < tcResults.size(); i++){
        tcResults[i].seq2json(file, space + "\t"); 
    }
    file << space <<  "] " << endl;  
    file << "}" << endl; 
    return true; 
}
 
bool TestCaseResult::seq2json(ofstream& file, string space){
    file << space << "{" << endl; 
    file << space << "'check' : " << check <<"' ," << endl; 
    file << space << "'msg' : " << msg <<"' ," << endl; 
    file << space << "} ," << endl; 
    return true; 
}