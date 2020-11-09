#include "JudgeResult.hpp"

using namespace std; 

TestCaseResult::TestCaseResult(bool c, string m, int _time, int _memory)
:check(c), msg(m), time(_time), memory(_memory){}; 
    

TestCaseResult::TestCaseResult(bool c, string m)
:check(c), msg(m), time(-1), memory(-1){}


string jsonEncoding(const string &s) {
    ostringstream encoded;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        if (*c == '"' || *c == '\\' || ('\x00' <= *c && *c <= '\x1f')) {
            encoded << "\\u"
              << hex << setw(4) << setfill('0') << (int)*c;
        } else {
            encoded << *c;
        }
    }
    return encoded.str();
}

ostream& operator<< (ostream& os, const TestCaseResult& tcRes){
    os << "check \t\t" << tcRes.check << endl; 
    os << "message \t\t" << tcRes.msg << endl; 
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
    file << space << "\"compile\" : " << compileResult << "," << endl; 
    file << space << "\"compile_msg\" : " << "\"" << jsonEncoding(compileMessage) << "\" ," << endl; 
    file << space << "\"result\" : [" << endl; 
    for(int i = 0; i < tcResults.size(); i++){
        tcResults[i].seq2json(file, space + "\t"); 
        if(i != tcResults.size() - 1)
            file << ", " << endl; 
        else 
            file << endl; 
    }
    file << space <<  "] " << endl;  
    file << "}" << endl; 
    return true; 
}
 
bool TestCaseResult::seq2json(ofstream& file, string space){
    file << space << "{" << endl; 
    file << space << "\"check\" : " << check << "," << endl; 
    file << space << "\"msg\" : \"" << msg <<"\"" << endl; 
    if(memory != -1)
        file << space << "\"memory\" : \"" << memory <<"\"" << endl; 
    if(time != -1)
        file << space << "\"time\" : \"" << time <<"\"" << endl; 
    file << space << "}"; 
    return true; 
}