#include "languageType.hpp"

Lang str2Lang(const char* str){
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
    else if (!strcmp(str, "C11")){
        res = C11; 
    }
    else if(!strcmp(str, "C99")){
        res = C99; 
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
      case C11:    return "C11";
      case C99:     return "C99";  
      default :     return "INVALID_LANG";
   }
   return "INVALID_LANG";
}