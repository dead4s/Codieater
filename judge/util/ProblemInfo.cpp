#include "ProblemInfo.hpp"

using namespace std; 

ProblemInfo::ProblemInfo(int t, int m, Lang l, string code, string data):
_time(t), _memory(m), _lang(l), _codeDir(code), _dataDir(data){}

ostream& operator << (ostream& os, const ProblemInfo& info){
    os << "===== ProblemInfo ====\n" 
    << "time limt = \t\t" << info._time << "\n"
    << "memory limit = \t\t" << info._time  << "\n"
    << "lang select = \t\t" <<  lang2Str(info._lang) << "\n"
    << "codeDir = \t\t" << info._codeDir << "\n"
    << "dataDir = \t\t" << info._dataDir << "\n";
    return os; 
}   

Lang str2Lang(char* str){
    Lang res; 
    if(!strcmp(str, "CPP11")){
        res = CPP11;
    }
    else if (!strcmp(str, "CPP14")){
        res = CPP14; 
    }
    else if (!strcmp(str, "CPP17")){
        res = CPP17; 
    }
    else if (!strcmp(str, "PYTHON2")){
        res = PYTHON2; 
    }
    else if (!strcmp(str, "PYTHON3")){
        res = PYTHON3; 
    }
    else if (!strcmp(str, "JAVA")){
        res = JAVA; 
    }
    else{
        throw invalid_argument("unsupported Language - invalid argument.");
    }
    return res; 
}

const char* lang2Str(enum Lang l) 
{
   switch (l) 
   {
      case CPP11: return "CPP11";
      case CPP14: return "CPP14";
      case CPP17: return "CPP17"; 
      case PYTHON2: return "PYTHON2";
      case PYTHON3: return "PYTHON3"; 
      case JAVA:    return "JAVA"; 
      default :     return "INVALID_LANG";
   }
   return "INVALID_LANG";
}