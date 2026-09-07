#ifndef C_DATA_STRUCTURES_HASHTABLE_H
#define C_DATA_STRUCTURES_HASHTABLE_H
#include<stddef.h>

typedef enum {
    HASH_TABLE_SUCCESS,
    HASH_TABLE_INVALID_CAPACITY,
    HASH_TABLE_ALLOCATION_FAILED,
    HASH_TABLE_INVALID_OUTPUT,
    HASH_TABLE_ALREADY_INITIALIZED,
    HASH_TABLE_INVALID_ARGUMENT,
    HASH_TABLE_INVALID_KEY,
    HASH_TABLE_DUPLICATE_KEY,
    HASH_TABLE_KEY_NOT_FOUND,
    HASH_TABLE_INVALID_VALUE,
    HASH_TABLE_INVALID_VALUE_SIZE,
    HASH_TABLE_CAPACITY_OVERFLOW,
}HashTableStatus;

typedef struct HashTable HashTable;
HashTableStatus createHashTable(size_t num_buckets, HashTable** table);
HashTableStatus searchHashTable(const HashTable* hash_table, const char* key, const void** output);
HashTableStatus hashTableInsertion(HashTable* hash_table, const char* key, const void* value, size_t value_size);
HashTableStatus hashTableDeletion(HashTable* hash_table, const char* key);

#endif //C_DATA_STRUCTURES_HASHTABLE_H
