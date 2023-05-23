#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_


#include "list.hpp"


struct HashTable {

    list_t *table;

    unsigned int (*hash) (const char *str);

    size_t size;
};


extern "C" int hashTableFindAsm (HashTable *ht, const char *str);

HashTable hashTableCtor     (size_t size, unsigned int (*hash) (const char *str));
void      hashTableDtor     (HashTable *ht);
void      hashTableListDtor (HashTable *ht, size_t id);
void      hashTableInsert   (HashTable *ht, const char *str);
int       hashTableFind     (HashTable *ht, const char *str);
void      hashTableDel      (HashTable *ht, const char *str);
size_t    hashTableGetCllsn (HashTable *ht, size_t id);

int strCmpFast (const char *str1, const char *str2);


#endif
