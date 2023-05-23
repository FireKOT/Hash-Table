#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "lib/config.hpp"
#include "lib/hashtable.hpp"
#include "lib/hashfuncs.hpp"
#include "lib/hash_test.hpp"


int main () {

    hashTestCllsn("words.txt", 950, hashStrSum, "testSupremum.txt");

    //clock_t time_start = clock();
    //hashTestFind("words.txt", 100, 1013, hashCRC32);
    //clock_t time_end = clock();
    //
    //printf("%lg,\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

    return 0;
}
