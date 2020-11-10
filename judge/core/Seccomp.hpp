#ifndef __SECCOM_H__
#define __SECCOM_H__

#include <iostream>
#include <vector> 
#include <seccomp.h> 
using namespace std; 

class Seccomp{
private:
    scmp_filter_ctx ctx;
    vector<int> whiteList = {
        //memory allocation
        SCMP_SYS(mprotect),
        SCMP_SYS(brk),
        SCMP_SYS(munmap),
        SCMP_SYS(mmap),
        //file
        SCMP_SYS(openat),
        SCMP_SYS(fstat),
        SCMP_SYS(read),
        SCMP_SYS(write),
        SCMP_SYS(writev),
        SCMP_SYS(lseek),
        SCMP_SYS(close),
        SCMP_SYS(pread64),
        //execvp 
        SCMP_SYS(open),
        SCMP_SYS(access),
        SCMP_SYS(execve),
        //other
        SCMP_SYS(arch_prctl),
        SCMP_SYS(exit_group),
        SCMP_SYS(execve),
    };

public: 
    Seccomp(){
        ctx = seccomp_init(SCMP_ACT_KILL); 
        if(!ctx)
            throw runtime_error("fail to init ctx in Seccomp constructor"); 
        for(int i = 0; i < whiteList.size(); i++){
            if( seccomp_rule_add(ctx, SCMP_ACT_ALLOW, whiteList[i], 0) != 0){
                throw runtime_error("fail to add scmp rule to ctx in Seccomp constructor"); 
            }
        }
    }

    bool startFilitering(){
        if(seccomp_load(ctx) != 0)
            return false; 
        seccomp_release(ctx); 
        return true; 
    }

    bool addAdditionalSeccomp(const vector<int>& wlist){
        for(int i = 0; i < wlist.size(); i++){
            if(seccomp_rule_add(ctx, SCMP_ACT_ALLOW, wlist[i], 0) != 0){
                throw runtime_error("fail to add scmp rule to ctx in Seccomp constructor"); 
            } 
        }
        return true; 
    }   
};

#endif 
