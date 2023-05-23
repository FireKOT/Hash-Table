#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "hash_test.hpp"
#include "hashtable.hpp"
#include "config.hpp"


void hashTestCllsn (const char *input_file_name, size_t size, unsigned int (*hash) (const char *str), const char *output_file_name) {

    RET_ON_VAL(!input_file_name, ERR_INV_ARG, );

    HashTable ht = hashTableCtor(size, hash);

    FILE *input = fopen(input_file_name, "r");
    RET_ON_VAL(!input, ERR_INV_ARG, );

    size_t count = 0;
    fscanf(input, "%ld", &count);

    char **words = loadWords(input, count);
    RET_ON_VAL(!words, ERR_NULL_PTR, );

    fclose(input);

    for (size_t id = 0; id < count; id++) {

        hashTableInsert(&ht, words[id]);
    }

    FILE *output = fopen(output_file_name, "w");
    RET_ON_VAL(!output, ERR_INV_ARG, );

    getCllsn(output, &ht);

    fclose(output);

    hashTableDtor(&ht);
    freeWords(words, count);
}

void hashTestFind (const char *input_file_name, size_t repeats, size_t size, unsigned int (*hash) (const char *str)) {

    RET_ON_VAL(!input_file_name, ERR_INV_ARG, );

    HashTable ht = hashTableCtor(size, hash);

    FILE *input = fopen(input_file_name, "r");
    RET_ON_VAL(!input, ERR_INV_ARG, );

    size_t count = 0;
    fscanf(input, "%ld", &count);

    char **words = loadWords(input, count);
    RET_ON_VAL(!words, ERR_NULL_PTR, );

    fclose(input);

    for (size_t id = 0; id < count; id++) {

        hashTableInsert(&ht, words[id]);
    }

    for (size_t iteration = 0; iteration < repeats; iteration++) {

        for (size_t id = 0; id < count; id++) {

            hashTableFind(&ht, words[id]);
        }
    }

    hashTableDtor(&ht);
    freeWords(words, count);
}

void getCllsn (FILE *out, HashTable *ht) {

    RET_ON_VAL(!out, ERR_INV_ARG, );

    for (size_t i = 0; i < ht->size; i++) {

        fprintf(out, "%ld\n", hashTableGetCllsn(ht, i));
    }
}

char **loadWords (FILE *input, size_t count) {

    RET_ON_VAL(!input, ERR_INV_ARG, nullptr);

    const size_t str_size = 32;

    char **words = (char**) calloc(count, sizeof(char*));
    RET_ON_VAL(!words, ERR_MEM_ALLOC, nullptr);

    for (size_t i = 0; i < count; i++) {

        char *str = (char*) aligned_alloc(32, str_size * sizeof(char));
        RET_ON_VAL(!str, ERR_MEM_ALLOC, nullptr);
        for (size_t ch = 0; ch < str_size; ch++) {

            str[ch] = 0;
        }

        fscanf(input, "%s", str);

        words[i] = str;
    }

    return words;
}

void freeWords (char **words, size_t count) {

    RET_ON_VAL(!words, ERR_INV_ARG, );

    for (size_t i = 0; i < count; i++) {

        free(words[i]);
    }

    free(words);
}