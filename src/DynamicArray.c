#include <stdint.h>
#include <stdlib.h>
#include "DynamicArray.h"

struct DynamicArray {
    int* data;
    size_t size;
    size_t capacity;
};

static DynamicArrayStatus ensureCapacity(DynamicArray* array) {
    if (array->size < array->capacity) {
        return DYNAMIC_ARRAY_SUCCESS;
    }

    if (array->capacity > SIZE_MAX / 2) {
        return DYNAMIC_ARRAY_CAPACITY_OVERFLOW;
    }

    const size_t new_capacity = array->capacity * 2;

    if (new_capacity > SIZE_MAX / sizeof(int)) {
        return DYNAMIC_ARRAY_CAPACITY_OVERFLOW;
    }

    int* temp = realloc(array->data, new_capacity * sizeof(int));
    if (temp == NULL) {
        return DYNAMIC_ARRAY_MEMORY_ALLOCATION_FAILED;
    }

    array->data = temp;
    array->capacity = new_capacity;

    return DYNAMIC_ARRAY_SUCCESS;
}

DynamicArrayStatus createDynamicArray(DynamicArray** array) {
    if (array == NULL) {
        return DYNAMIC_ARRAY_INVALID_ARGUMENT;
    }
    if (*array != NULL) {
        return DYNAMIC_ARRAY_INVALID_OUTPUT;
    }

    DynamicArray* new_array = malloc(sizeof(DynamicArray));
    if (new_array == NULL) {
        return DYNAMIC_ARRAY_MEMORY_ALLOCATION_FAILED;
    }

    new_array->size = 0;
    new_array->capacity = 4;
    new_array->data = malloc(new_array->capacity * sizeof(int));

    if (new_array->data == NULL) {
        free(new_array);
        return DYNAMIC_ARRAY_MEMORY_ALLOCATION_FAILED;
    }

    *array = new_array;

    return DYNAMIC_ARRAY_SUCCESS;
}

DynamicArrayStatus addDynamicArray(DynamicArray* array, const int value) {
    if (array == NULL) {
        return DYNAMIC_ARRAY_INVALID_ARGUMENT;
    }

    const DynamicArrayStatus status = ensureCapacity(array);
    if (status != DYNAMIC_ARRAY_SUCCESS) {
        return status;
    }

    array->data[array->size] = value;
    array->size++;

    return DYNAMIC_ARRAY_SUCCESS;
}

DynamicArrayStatus removeDynamicArray(DynamicArray* array, const size_t index) {
    if (array == NULL) {
        return DYNAMIC_ARRAY_INVALID_ARGUMENT;
    }
    if (index >= array->size) {
        return DYNAMIC_ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    // Removal does not preserve element order.
    array->data[index] = array->data[array->size - 1];
    array->size--;

    return DYNAMIC_ARRAY_SUCCESS;
}

DynamicArrayStatus getDynamicArray(const DynamicArray* array, const size_t index, int* output) {
    if (array == NULL) {
        return DYNAMIC_ARRAY_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return DYNAMIC_ARRAY_INVALID_OUTPUT;
    }
    if (index >= array->size) {
        return DYNAMIC_ARRAY_INDEX_OUT_OF_BOUNDS;
    }

    *output = array->data[index];

    return DYNAMIC_ARRAY_SUCCESS;
}

DynamicArrayStatus destroyDynamicArray(DynamicArray** array) {
    if (array == NULL || *array == NULL) {
        return DYNAMIC_ARRAY_INVALID_ARGUMENT;
    }

    free((*array)->data);
    free(*array);
    *array = NULL;

    return DYNAMIC_ARRAY_SUCCESS;
}