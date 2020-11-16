#include "JudgeResult.hpp"

using namespace std; 

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

stringstream JudgeResult::seq2json(string space){
    stringstream jsonForm; 
    jsonForm << "{" << endl;
    jsonForm << space << "\"compile\" : " << compileResult << "," << endl; 
    jsonForm << space << "\"compile_msg\" : " << "\"" << jsonEncoding(compileMessage) << "\" ," << endl; 
    jsonForm << space << "\"result\" : [" << endl; 
    for(int i = 0; i < tcResults.size(); i++){
        jsonForm << tcResults[i].seq2json(space + "\t").rdbuf();  
        if(i != tcResults.size() - 1)
            jsonForm << ", " << endl; 
        else 
            jsonForm << endl; 
    }
    jsonForm << space <<  "] " << endl;  
    jsonForm << "}" << endl; 
    return jsonForm; 
}
