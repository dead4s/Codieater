#include <iostream>
#include <string> 
#include <unistd.h>
#include <stdexcept> 
#include <cstdlib> 

#include "util/ProblemInfo.hpp"
#include "util/parse.hpp"
#include "config.hpp"
#include "lang/ExecuteBox.hpp"

using namespace std; 


int main(int argc, char* argv[]){

    setEnv(); 

    ProblemInfo pinfo = parseInput(argc, argv); 
    cout << pinfo << endl; 

    ExecuteBox xbox(pinfo); 
    xbox.compile(); 

    return 0;
}