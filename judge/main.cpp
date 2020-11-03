#include <iostream>
#include <string> 
#include <unistd.h>
#include <stdexcept> 
#include <cstdlib> 

#include "util/ProblemInfo.hpp"
#include "util/parse.hpp"
#include "config.hpp"
#include "lang/ExecuteBox.hpp"
#include "JudgeResult.hpp"

using namespace std; 


int main(int argc, char* argv[]){

    setEnv(); 

    ProblemInfo pinfo = parseInput(argc, argv); 
    cout <<"== PromblemInfo DUMP ==" << endl; 
    cout << pinfo << endl; 

    ExecuteBox xbox(pinfo); 
    JudgeResult result; 

    char compileMsg[COMPILE_MSG_LENGTH]; 
    bool compileResult = xbox.compile(compileMsg, COMPILE_MSG_LENGTH); 
    result.compileResult = compileResult; 
    result.compileMessage = string(compileMsg); 

    cout <<"== JudgeResult DUMP ==" << endl; 
    cout << result << endl; 

    ofstream resultFile(MARKPATH + pinfo.getMarkNo() + "/result.json"); 
    result.seq2json(resultFile); 
    resultFile.close(); 

    return 0;
}