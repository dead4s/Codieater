#include <iostream>
#include <string> 
#include <unistd.h>
#include <stdexcept> 
#include "util/ProblemInfo.hpp"
#include "util/parse.hpp"

using namespace std; 

int main(int argc, char* argv[]){

    ProblemInfo pinfo = parseInput(argc, argv); 
    cout << pinfo << endl; 

    return 0;
}