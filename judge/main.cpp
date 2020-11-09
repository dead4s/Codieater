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

int getTestCasesCount(){
    int count; 
    string countCommand = "ls -l " + PROBPATH + "/in/" + "*[0-9].in | wc -l"; 
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
    cout <<"compile : " << result.compileResult << endl;
    cout <<"compile Message : " << result.compileMessage << endl; 

    if(compileResult){
        int count = getTestCasesCount(); 
        for(int i = 1; i <= count; i++){
            int memUsed; //KB
            int timeUsed; //milliSec
            ExeResult runtimeCheck = xbox.executeTC(i, memUsed, timeUsed); 

            TestCaseResult* tcResult; 
            bool correctCheck; 
            switch (runtimeCheck)
            {
            case MEM_LIM_EXCEED:
                tcResult = new TestCaseResult(false, "Memory Limit Exceeded"); 
                break;
            case TIME_LIM_EXCEED: 
                tcResult = new TestCaseResult(false, "Time Limit Exceeded"); 
                break; 
            case RUNT_ERR:
                tcResult = new TestCaseResult(false, "Runtime Error");
                break; 
            case GOOD : 
                correctCheck = cmpFiles(i); 
                if(correctCheck)
                    tcResult = new TestCaseResult(true, "Correct", timeUsed, memUsed); 
                else 
                    tcResult = new TestCaseResult(false, "Wrong Answer");        
                break; 
            default:
                tcResult = new TestCaseResult(false, "JudgeSystem Internal Error");   
                break;
            }
            tcResult->seq2json(cout, ""); 
            cout << endl; 
            result.tcResults.push_back(*tcResult); 
            delete tcResult; 
        }
    }
   
    ofstream resultFile(MARKPATH + "/result.json"); 
    result.seq2json(resultFile); 
    resultFile.close(); 

    return 0;
}