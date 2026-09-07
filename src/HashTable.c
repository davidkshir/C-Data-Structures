#include "HashTable.h"
#include<stdint.h>
#include<stdlib.h>


typedef struct Entry {
    char *key ;
    void* value;
    uint64_t cached_hash;
    struct Entry *next;
} Entry;

struct HashTable{
    Entry **buckets;
    size_t num_buckets;
    size_t size;
};

const static uint64_t FNV1a_OFFSET_BASIS = UINT64_C(14695981039346656037);
const static uint64_t FNV1a_PRIME = UINT64_C(1099511628211);

static uint64_t hashFNV1a(const char *item){
    uint64_t hash = FNV1a_OFFSET_BASIS;
    for (size_t i = 0; item[i] != '\0'; i++) {
        uint8_t const cur_char = item[i];
        hash ^= cur_char;
        hash *= FNV1a_PRIME;
    }
    return hash;
}

static size_t hashToIndex(const uint64_t hash, const size_t numBuckets) {
    return hash % numBuckets;
}

HashTableStatus createHashTable(const size_t num_buckets, HashTable** table) {
    if (num_buckets == 0) {
        return HASH_TABLE_INVALID_CAPACITY;
    }
    if (table == NULL) {
        return HASH_TABLE_INVALID_OUTPUT;
    }
    if (*table != NULL) {
        return HASH_TABLE_ALREADY_INITIALIZED;
    }

    HashTable* hash_table = malloc(sizeof(HashTable));
    if (hash_table == NULL) {
        return HASH_TABLE_ALLOCATION_FAILED;
    }

    Entry** buckets = calloc(num_buckets, sizeof(Entry*));
    if (buckets == NULL) {
        free(hash_table);
        return HASH_TABLE_ALLOCATION_FAILED;
    }

    hash_table->buckets = buckets;
    hash_table->num_buckets = num_buckets;
    hash_table->size = 0;
    *table = hash_table;

    return HASH_TABLE_SUCCESS;
}