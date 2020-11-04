#ifndef __GRADE_H__
#define __GRADE_H__

#include <string> 
#include <fstream> 
#include <iostream> 
#include "../system/config.hpp"

using namespace std; 


string trim(const string s){
    int endindex = s.size(); 
    while(isspace(s[endindex-1])){
        endindex--;
    }
    return s.substr(0, endindex); 
}

void checkIstream(istream& in, string name){
    if(in.good()){
        cout << name <<" is good" << endl; 
    }
    else{
        if(in.bad())
            cout << name << " is bad" << endl; 
        if(in.eof())
            cout << name << " is eof" << endl; 
    }
    return;
}

bool checkEmptystream(string start, istream& in){
    start = trim(start); 
    if(start.compare("") != 0){
        return false; 
    }
    string line; 
    while(getline(in, line)){
        line = trim(line); 
        if(line.compare("") != 0)
            return false; 
    }
    if(!in.eof())
        throw runtime_error("error in checkEmptyString"); 
    return true; 
}


bool cmpFiles(string prob_no, string mark_no, int fileNo){
    string sfileNo = to_string(fileNo); 
    string proboutput = PROBPATH + prob_no + "/out/" + sfileNo + ".out"; 
    string markoutput = MARKPATH + mark_no + "/" + sfileNo + ".out"; 

    ifstream in1(proboutput, ios::in); 
    ifstream in2(markoutput, ios::in);
    if(!in1){
        throw logic_error("fail to open file " + proboutput); 
    }
    if(!in2){
        throw logic_error("fail to open file " + markoutput); 
    }

    string line1; 
    string line2; 

    bool success = true; 

    bool eof1 = in1.eof(); 
    bool eof2 = in2.eof(); 
    while((!eof1) && (!eof2)){
        getline(in1, line1); 
        eof1 = in1.eof(); 

        getline(in2, line2);
        eof2 = in2.eof(); 

        line1 = trim(line1); 
        line2 = trim(line2); 
        //cout << line1 << ", " << line2 << endl; 
        if ( line1.compare(line2) == 0){ 
            continue; 
        }
        else{
            success = false; 
            break; 
        }
    }

    if(success == false)
        return false; 
    if(in1.eof() && in2.eof()){
        //cout <<"both file end successfully" << endl; 
        return true; 
    }
    else if(in1.bad() || in2.bad()){
        throw runtime_error("fail to read your files"); 
    }

    if(!in1.eof()){ //in1 is not fininshed..
        return checkEmptystream(line1, in1); 
    }
    if(!in2.eof())
        return checkEmptystream(line2, in2); 
    return false; 
}
#endif 