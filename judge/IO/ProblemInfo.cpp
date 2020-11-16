#include "ProblemInfo.hpp"

using namespace std; 

ProblemInfo::ProblemInfo(int t, int m, int s, Lang l):
_time(t), _heap(m), _lang(l), _stack(s){};


ProblemInfo::ProblemInfo():_time(2000), _heap(512), _stack(1), _lang(CPP14){}; 


ProblemInfo::ProblemInfo(const ProblemInfo& p)
:_time(p._time), _heap(p._heap), _stack(p._stack), _lang(p._lang){}; 


ostream& operator << (ostream& os, const ProblemInfo& info){
    os << "===== ProblemInfo ====\n" 
    << "time limt = \t\t" << info._time << "\n"
    << "heap limit = \t\t" << info._heap  << "\n"
    << "stack limit = \t\t" << info._stack  << "\n"
    << "lang select = \t\t" <<  lang2Str(info._lang) << "\n";
    return os; 
}   