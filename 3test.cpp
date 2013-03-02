// headers and includes
using namespace std;
#include <fstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include "Cache.h"

// global variables
long secret = time(NULL);
#define fff(x) ( (long) int(100*(sin(x)+cos(x))) )

// constants
const long compLoop = 10000;  // the number of times to compute "complicated" to simulate a cache miss

char complicated(char aa, char bb, char cc, char dd) {
    // a complicated function that requires some processing and is difficult to invert
    return (fff(fff(fff(fff(aa+secret%(fff(bb)+129) + fff(fff(secret)*secret)%(fff(cc)+129)%253+fff(dd)))%256 - 128)));
}

int main() {
    // declarations
    int num1,num2,num3,num4; // for input
    char aa, bb, cc, dd;     // IP components
    long cacheMiss=0;        // the number of cache misses
    long cacheRequests=0;    // the number of cache requests
    
    // initializations
    Cache yourCache;
    ifstream file("iptrace1.txt"); // open the file for input;
    if (!file) {printf("File 'iptrace.txt' is not available.\n"); exit(-1);}
    int startTime = time(NULL);
    // read in input file and apply the cache
    while (!file.eof() && cacheRequests < 10000) {
        cacheRequests++;
        char dot;
        file >> num1 >> dot >> num2 >> dot >> num3 >> dot >> num4;
        // convert to chars
        aa=num1; bb=num2; cc=num3; dd=num4;
        try{
            if (yourCache.lookup(aa,bb,cc,dd)!=complicated(aa,bb,cc,dd)) {
                cout << "ERROR:  Your cache contains incorrect data!" << endl;
                exit(-1);
            };
        }
        catch (int ii) {
            // a Cache miss occurred; allow the Cache to insert the code
            if (ii!=0) // only deal with thrown code 0
            { cout << "Unknown exception code " << ii
                << endl; exit(-1); }
            char code;
            // do some time-consuming computations to simulate a cache miss
            for (long ii=0; ii<compLoop; ii++)
                code = complicated(aa,bb,cc,dd);
            yourCache.insert(aa,bb,cc,dd,code);
            cacheMiss++;
            //cout << "Cache miss on " << num1 << "." << num2
            //<< "." << num3 << "." << num4 << ": " << ((int) code) << endl;
        }
    }
    
    int endTime = time(NULL);
    cout << "Cache processing completed in " << (endTime-startTime)
    << " seconds!" << endl
    << "Cache requests: " << cacheRequests << endl
    << "Cache misses:   " << cacheMiss << endl
    << "Cache hit rate: " << 100*(1.0 - (float) cacheMiss/cacheRequests) << "%" << endl;
    cout << "ALL DONE" << endl; // signals that everything worked fine
}