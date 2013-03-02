#ifndef CACHE
#define CACHE

#include <iostream>
using namespace std;

class Cache {
public:
    Cache();            // initializes the Cache
    char lookup(char aa, char bb, char cc, char dd);
    /* Looks up IP address aa.bb.cc.dd in the cache
     ** Returns the code corresponding to the address if it is in the cache
     **    or throws code "0" if the address was not found in the cache
     */
    
    void insert(char aa, char bb, char cc, char dd, char code);
    /* Requests that the cache insert an entry with
     ** IP aa.bb.cc.dd and code "code".  The cache could choose to
     ** ignore this request if it wants.
     */
    
private:
    char memory[1000];  // main memory
    int registers[5];   // some registers
    int ii,jj,kk;       // some looping variables
};

#endif