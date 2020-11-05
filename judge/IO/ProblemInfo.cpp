#include "ProblemInfo.hpp"

using namespace std; 

ProblemInfo::ProblemInfo(int t, int m, Lang l):
_time(t), _memory(m), _lang(l){};


ProblemInfo::ProblemInfo():_time(2000), _memory(512), _lang(CPP14){}; 


ProblemInfo::ProblemInfo(const ProblemInfo& p)
:_time(p._time), _memory(p._memory), _lang(p._lang){}; 


ostream& operator << (ostream& os, const ProblemInfo& info){
    os << "===== ProblemInfo ====\n" 
    << "time limt = \t\t" << info._time << "\n"
    << "memory limit = \t\t" << info._memory  << "\n"
    << "lang select = \t\t" <<  lang2Str(info._lang) << "\n";
    return os; 
}   