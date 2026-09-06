#include "HashTable.h"
#include <stdint.h>
#include <stdio.h>

const static uint64_t FNV_OFFSET_BIAS = UINT64_C(14695981039346656037);
const static uint64_t FNV_PRIME = UINT64_C(1099511628211);

uint64_t hashFNV(const char *item){
    uint64_t hash = FNV_OFFSET_BIAS;
    for (size_t i = 0; item[i] != '\0'; i++) {
        uint8_t const cur_char = item[i];
        hash ^= cur_char;
        hash *= FNV_PRIME;
    }
    return hash;
}