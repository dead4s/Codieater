#ifndef __LANGTYPE__H_
#define __LANGTYPE__H_
#include <cstring>
#include <stdexcept>

using namespace std; 

enum Lang {CPP11, CPP14, CPP17, PYTHON2, PYTHON3, C11, C99, INVALID}; 

Lang str2Lang(const char* str);

const char* lang2Str(enum Lang l);

#endif