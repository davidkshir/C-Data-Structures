#ifndef C_DATA_STRUCTURES_HASHTABLE_H
#define C_DATA_STRUCTURES_HASHTABLE_H
#include<stddef.h>

typedef enum {
    HASH_TABLE_SUCCESS,
    HASH_TABLE_INVALID_CAPACITY,
    HASH_TABLE_ALLOCATION_FAILED,
    HASH_TABLE_INVALID_OUTPUT,
    HASH_TABLE_ALREADY_INITIALIZED
}HashTableStatus;

typedef struct HashTable HashTable;
HashTableStatus createHashTable(size_t num_buckets, HashTable** table);

#endif //C_DATA_STRUCTURES_HASHTABLE_H
