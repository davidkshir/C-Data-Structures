#include "HashTable.h"
#include <stdint.h>
#include <stdio.h>

const static uint64_t FNV1a_OFFSET_BIAS = UINT64_C(14695981039346656037);
const static uint64_t FNV1a_PRIME = UINT64_C(1099511628211);

static uint64_t hashFNV1a(const char *item){
    uint64_t hash = FNV1a_OFFSET_BIAS;
    for (size_t i = 0; item[i] != '\0'; i++) {
        uint8_t const cur_char = item[i];
        hash ^= cur_char;
        hash *= FNV1a_PRIME;
    }
    return hash;
}