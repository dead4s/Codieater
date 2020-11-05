#include <iostream>
#include <string> 
#include <unistd.h>
#include <stdexcept> 
#include <cstdlib> 

#include "IO/ProblemInfo.hpp"
#include "IO/JudgeResult.hpp"
#include "system/parse.hpp"
#include "system/config.hpp"
#include "core/grade.hpp"
#include "core/ExecuteBox.hpp"


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
            int memUsed; 
            ExeResult runtimeCheck = xbox.executeTC(i, memUsed); 
            bool correctCheck; 
            //get memory usage test
            //cout << memUsed << "Kb" << endl; 
            if(runtimeCheck == MEM_LIM_EXCEED){
                result.tcResults.emplace_back(false, "MemoryLimitExceeded"); 
            }
            else if(runtimeCheck == TIME_LIM_EXCEED){
                result.tcResults.emplace_back(false, "TimeLimitExceeded");
            }
            else if(runtimeCheck == RUNT_ERR){
                result.tcResults.emplace_back(false, "RuntimeError"); 
            }
            else if(runtimeCheck == JUDGE_ERR){
                result.tcResults.emplace_back(false, "JudgeSystemInternalError"); 
            }
            else if(runtimeCheck == GOOD){
                correctCheck = cmpFiles(pinfo.getProbNo(), pinfo.getMarkNo(), i); 
                if(correctCheck == true){
                    result.tcResults.emplace_back(true, "Correct");
                }
                else{
                    result.tcResults.emplace_back(false, "WrongAnswer");
                }               
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