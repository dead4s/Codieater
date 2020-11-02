#include "CPP_14.hpp"

vector<string> CPP_14::saveArg = {
    "-o", "main",
    "-O2", 
    "-lm",
    "-Wall",
    "-static",
    "-std=gnu++14",     
    "Main.cpp"
};

vector<string> CPP_14::saveEnv = {
};

const string CPP_14::compiler = "/usr/bin/g++"; 
const string CPP_14::srcFile = "Main.cpp"; 