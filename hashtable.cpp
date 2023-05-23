#include <stdio.h>
#include <malloc.h>
#include <string.h> 
#include <immintrin.h>

#include "hashtable.hpp"
#include "list.hpp"
#include "config.hpp"


HashTable hashTableCtor (size_t size, unsigned int (*hash) (const char *str)) {

    HashTable err {

        .table     = nullptr,
        .hash      = nullptr,
        .size      = 0,
    };

    RET_ON_VAL(!size, ERR_INV_ARG, err);

    list_t *table = (list_t*) calloc(size, sizeof(list_t));
    RET_ON_VAL(!table, ERR_MEM_ALLOC, err);

    for (size_t i = 0; i < size; i++) {

        table[i] = ListCtor();
    }

    return {

        .table     = table,
        .hash      = hash,
        .size      = size,
    };
}

void hashTableDtor (HashTable *ht) {

    RET_ON_VAL(!ht, ERR_INV_ARG, );

    for (size_t id = 0; id < ht->size; id++) {

        hashTableListDtor(ht, id);
    }

    free(ht->table);
    ht->table = nullptr;

    ht->hash = nullptr;
    ht->size = 0;
}

void hashTableListDtor (HashTable *ht, size_t id) {

    RET_ON_VAL(!ht || ht->size <= id, ERR_INV_ARG, );

    ListDtor(&ht->table[id]);
}

void hashTableInsert (HashTable *ht, const char *str) {

    RET_ON_VAL(!ht || !str, ERR_INV_ARG, );

    unsigned int hash = ht->hash(str);

    PushTail(&ht->table[hash % ht->size], str);
}

int hashTableFind (HashTable *ht, const char *str) {

    RET_ON_VAL(!ht || !str, ERR_INV_ARG, 0);

    size_t id = ht->hash(str) % ht->size;
    size_t cur_node_id = ht->table[id].head;

    for (size_t i = 0; i < ht->table[id].size; i++) {

        if (!strcmp(str, ht->table[id].data[cur_node_id].value)) {

            return true;
        }

        cur_node_id = ht->table[id].data[cur_node_id].next;
    }

    return false;
}

void hashTableDel (HashTable *ht, const char *str) {

    RET_ON_VAL(!ht || !str, ERR_INV_ARG, );

    size_t id = ht->hash(str) % ht->size;
    size_t cur_node_id = ht->table[id].head;

    for (size_t i = 0; i < ht->table[id].size; i++) {

        if (!strcmp(str, ht->table[id].data[cur_node_id].value)) {

            ListPop(&ht->table[id], cur_node_id);
            return;
        }

        cur_node_id = ht->table[id].data[cur_node_id].next;
    }
}

size_t hashTableGetCllsn (HashTable *ht, size_t id) {

    RET_ON_VAL(!ht || id >= ht->size, ERR_INV_ARG, 0);

    return ht->table[id].size;
}

int strCmpFast (const char *str1, const char *str2) {

    __m256i _str1 = _mm256_load_si256((const __m256i*) str1);
    __m256i _str2 = _mm256_load_si256((const __m256i*) str2);

    __m256i cmp = _mm256_cmpeq_epi8(_str1, _str2);

    return ~_mm256_movemask_epi8(cmp);
}

