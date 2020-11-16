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
            TestCaseResult tcResult = xbox.executeTC(i); 
            if(tcResult.getCheck()){
                bool correctCheck = cmpFiles(i); 
                if(correctCheck == true)
                    tcResult.setResult(CORRECT); 
                else
                    tcResult.setResult(WRONG); 
            }
            stringstream jsform = tcResult.seq2json(); 
            cout << jsform.rdbuf(); 
            cout << endl; 
            result.tcResults.push_back(tcResult); 
        }
    }
   
    ofstream resultFile(MARKPATH + "/result.json"); 
    stringstream jsform = result.seq2json(); 
    resultFile << jsform.rdbuf(); 
    resultFile.close(); 

    return 0;
}