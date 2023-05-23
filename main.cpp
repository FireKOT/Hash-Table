#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "config.hpp"
#include "hashtable.hpp"
#include "hashfuncs.hpp"
#include "hash_test.hpp"


void getData (const char *file) {

    FILE *in = fopen(file, "r");

    long long sum = 0;
    for (int i = 0; i < 1013; i++) {

        long long tmp = 0;
        fscanf(in, "%lld", &tmp);

        sum += (tmp - 57) * (tmp - 57);
    }

    printf("%lg\n", sqrt((double) sum / 1013));

    fclose(in);
}


int main () {

    //hashTestCllsn("words.txt", 11777, hashCRC32Fast, "test.txt");

    //FILE *out = fopen("rezults.txt", "w");
//
    //for (int i = 0; i < 20; i++) {
//
    //    clock_t time_start = clock();
    //    hashTestFind("words.txt", 100, 1013, hashCRC32);
    //    clock_t time_end = clock();
    //    
    //    fprintf(out, "%lg,\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);
    //}
    //
    //fclose(out);

    getData("plotdata/hashCRC32Cllsn.txt");

    return 0;
}
