#ifndef C_DATA_STRUCTURES_DYNAMICARRAY_H
#define C_DATA_STRUCTURES_DYNAMICARRAY_H

#include <stddef.h>

typedef enum {
    DYNAMIC_ARRAY_SUCCESS,
    DYNAMIC_ARRAY_MEMORY_ALLOCATION_FAILED,
    DYNAMIC_ARRAY_INDEX_OUT_OF_BOUNDS,
    DYNAMIC_ARRAY_INVALID_ARGUMENT,
    DYNAMIC_ARRAY_INVALID_OUTPUT,
    DYNAMIC_ARRAY_CAPACITY_OVERFLOW
} DynamicArrayStatus;

typedef struct DynamicArray DynamicArray;

DynamicArrayStatus createDynamicArray(DynamicArray** array);
DynamicArrayStatus destroyDynamicArray(DynamicArray** array);

DynamicArrayStatus addDynamicArray(DynamicArray* array, int value);
DynamicArrayStatus removeDynamicArray(DynamicArray* array, size_t index);
DynamicArrayStatus getDynamicArray(const DynamicArray* array, size_t index, int* output);

#endif //C_DATA_STRUCTURES_DYNAMICARRAY_H
