#ifndef _HASH_TEST_HPP_
#define _HASH_TEST_HPP_


#include "hashtable.hpp"


void   hashTestCllsn (const char *input_file_name, size_t size, unsigned int (*hash) (const char *str), const char *output_file_name);
void   hashTestFind  (const char *input_file_name, size_t repeats, size_t size, unsigned int (*hash) (const char *str));
void   getCllsn      (FILE *out, HashTable *ht);
char **loadWords     (FILE *input,  size_t count);
void   freeWords     (char **words, size_t count);


#endif