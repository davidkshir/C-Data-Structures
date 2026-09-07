#include "HashTable.h"
#include<stdint.h>
#include<stdlib.h>
#include <string.h>


typedef struct Entry {
    char* key ;
    void* value;
    size_t value_size;
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

HashTableStatus searchHashTable(const HashTable* hash_table, const char* key, const void** output) {
    if (hash_table == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (key == NULL) {
        return HASH_TABLE_INVALID_KEY;
    }
    if (output == NULL) {
        return HASH_TABLE_INVALID_OUTPUT;
    }
    if (*output != NULL) {
        return HASH_TABLE_INVALID_OUTPUT;
    }

    const uint64_t hash = hashFNV1a(key);
    const size_t index = hashToIndex(hash, hash_table->num_buckets);

    const Entry* cur = hash_table->buckets[index];
    while (cur != NULL) {
        if (cur->cached_hash != hash) {
            cur = cur->next;
            continue;
        }
        if (strcmp(key, cur->key) == 0) {
            *output = cur->value;
            return HASH_TABLE_SUCCESS;

        }
        cur = cur->next;
    }
    return HASH_TABLE_KEY_NOT_FOUND;
}

static HashTableStatus resizeHashTable(HashTable* hash_table) {
    if (hash_table == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }

    if (hash_table->num_buckets > SIZE_MAX / 2) {
        return HASH_TABLE_CAPACITY_OVERFLOW;
    }
    const size_t new_capacity = 2 * hash_table->num_buckets;
    Entry** buckets = calloc(new_capacity, sizeof(Entry*));
    if (buckets == NULL) {
        return HASH_TABLE_ALLOCATION_FAILED;
    }

    for (size_t i = 0; i < hash_table->num_buckets ; i++) {
        if (hash_table->buckets[i] == NULL) {
            continue;
        }
        Entry* cur = hash_table->buckets[i];
        while (cur != NULL){
            Entry* tmp_ptr = cur->next;
            const size_t new_index = hashToIndex(cur->cached_hash, new_capacity);
            cur->next = buckets[new_index];
            buckets[new_index] = cur;
            cur = tmp_ptr;
        }
    }

    free(hash_table->buckets);
    hash_table->buckets = buckets;
    hash_table->num_buckets = new_capacity;
    return HASH_TABLE_SUCCESS;
}

HashTableStatus hashTableInsertion(HashTable* hash_table, const char* key, const void* value, const size_t value_size) {
    if (hash_table == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (key == NULL) {
        return HASH_TABLE_INVALID_KEY;
    }
    if (value == NULL) {
        return HASH_TABLE_INVALID_VALUE;
    }
    if (value_size == 0) {
        return HASH_TABLE_INVALID_VALUE_SIZE;
    }

    const uint64_t hash = hashFNV1a(key);

    const void* output = NULL;
    const HashTableStatus search_status = searchHashTable(hash_table, key, &output);
    if (search_status == HASH_TABLE_SUCCESS) {
        return HASH_TABLE_DUPLICATE_KEY;
    }
    if (search_status != HASH_TABLE_KEY_NOT_FOUND) {
        return search_status;
    }


    if ((float) (hash_table->size + 1) / (float) hash_table->num_buckets >= 0.75f) {
        const HashTableStatus status = resizeHashTable(hash_table);
        if (status != HASH_TABLE_SUCCESS) {
            return status;
        }
    }

    const size_t index = hashToIndex(hash, hash_table->num_buckets);
    const size_t key_len = strlen(key) + 1; // +1 to include '\0'

    Entry* entry = malloc(sizeof(Entry));
    char* key_copy = malloc(key_len);
    void* value_copy = malloc(value_size);

    if (entry == NULL || key_copy == NULL || value_copy == NULL){
        free(entry);
        free(key_copy);
        free(value_copy);
        return HASH_TABLE_ALLOCATION_FAILED;
    }

    memcpy(key_copy, key, key_len);
    memcpy(value_copy, value, value_size);

    entry->key = key_copy;
    entry->value = value_copy;
    entry->cached_hash = hash;
    entry->value_size = value_size;
    entry->next = hash_table->buckets[index];
    hash_table->buckets[index] = entry;
    hash_table->size += 1;

    return HASH_TABLE_SUCCESS;
}
