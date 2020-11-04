#include "ProblemInfo.hpp"

using namespace std; 

ProblemInfo::ProblemInfo(int t, int m, Lang l, string code, string data):
_time(t), _memory(m), _lang(l), _markNo(code), _probNo(data){};


ProblemInfo::ProblemInfo():_time(2000), _memory(512), _lang(CPP14), _markNo(""), _probNo(""){}; 


ProblemInfo::ProblemInfo(const ProblemInfo& p)
:_time(p._time), _memory(p._memory), _lang(p._lang), _markNo(p._markNo), _probNo(p._probNo){}; 


ostream& operator << (ostream& os, const ProblemInfo& info){
    os << "===== ProblemInfo ====\n" 
    << "time limt = \t\t" << info._time << "\n"
    << "memory limit = \t\t" << info._memory  << "\n"
    << "lang select = \t\t" <<  lang2Str(info._lang) << "\n"
    << "codeDir = \t\t" << info._markNo << "\n"
    << "dataDir = \t\t" << info._probNo << "\n";
    return os; 
}   