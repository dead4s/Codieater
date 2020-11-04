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
#include "grade.hpp"

using namespace std; 

int getTestCasesCount(string probNo){
    int count; 
    string countCommand = "ls -l " + PROBPATH + probNo + "/in/" + "*[0-9].in | wc -l"; 
    FILE* countFile = popen(countCommand.c_str(), "r"); 
    fscanf(countFile, "%d", &count); 
    fclose(countFile);     
    return count; 
}

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

    if(compileResult){
        int count = getTestCasesCount(pinfo.getProbNo()); 
        for(int i = 1; i < count; i++){
            bool runtimeCheck = xbox.gradeTestCase(i); 
            bool correctCheck; 
            if(runtimeCheck){
                correctCheck = cmpFiles(pinfo.getProbNo(), pinfo.getMarkNo(), i); 
                if(correctCheck == true){
                    result.tcResults.emplace_back(true, "correct");
                }
                else{
                    result.tcResults.emplace_back(false, "wrong answer");
                }
            }
            else {
                result.tcResults.emplace_back(false, "runtimeError");
            }
        }
    }
    
    cout <<"== JudgeResult DUMP ==" << endl; 
    cout << result << endl; 

    ofstream resultFile(MARKPATH + pinfo.getMarkNo() + "/result.json"); 
    result.seq2json(resultFile); 
    resultFile.close(); 

    return 0;
}