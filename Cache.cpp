#include "Cache.h"

Cache::Cache(){
    for (ii = 0; ii < 5; ii++)
        registers[ii] = 0;
    ii = 0;
    jj = 0;
    kk = 0;
}

char Cache::lookup(char aa, char bb, char cc, char dd){
    for (ii = 0; ii < 5; ii++){
        if (memory[registers[ii]] == aa && memory[registers[ii]+1] == bb && memory[registers[ii]+2] == cc && memory[registers[ii]+3] == dd)
            return memory[registers[ii]+4];
    }
    for (ii = 0; ii < 1000; ii = ii + 5) {
        if (memory[ii] == aa && memory[ii+1] == bb && memory[ii+2] == cc && memory[ii+3] == dd)
            return memory[ii+4];
    }
    throw 0;
}

void Cache::insert(char aa, char bb, char cc, char dd, char code){
    if (jj < 1000) {
        memory[jj++] = aa;
        memory[jj++] = bb;
        memory[jj++] = cc;
        memory[jj++] = dd;
        memory[jj++] = code;
    }
    else {
        while (kk == registers[0] || kk == registers[1] || kk == registers[2] || kk == registers[3] || kk == registers[4]) {
            kk = kk + 5;
            if (kk >= 1000)
                kk = 0;
        }
        memory[kk] = aa;
        memory[kk+1] = bb;
        memory[kk+2] = cc;
        memory[kk+3] = dd;
        memory[kk+4] = code;
        registers[4] = registers[3];
        registers[3] = registers[2];
        registers[2] = registers[1];
        registers[1] = registers[0];
        registers[0] = kk;
        kk = kk + 5;
        if (kk >= 1000)
            kk = 0;
    }
    
}