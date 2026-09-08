#include <stdint.h>
#include <stdlib.h>
#include "Stack.h"

struct Stack {
    int* data;
    size_t top;
    size_t capacity;
};

StackStatus createStack(Stack** stack) {
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }
    if (*stack != NULL) {
        return STACK_INVALID_OUTPUT;
    }

    Stack* new_stack = malloc(sizeof(Stack));
    if (new_stack == NULL) {
        return STACK_MEMORY_ALLOCATION_FAILED;
    }

    new_stack->top = 0;
    new_stack->capacity = 4;
    new_stack->data = malloc(new_stack->capacity * sizeof(int));

    if (new_stack->data == NULL) {
        free(new_stack);
        return STACK_MEMORY_ALLOCATION_FAILED;
    }

    *stack = new_stack;

    return STACK_SUCCESS;
}

StackStatus pushStack(Stack* stack, const int data) {
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    if (stack->top == stack->capacity) {
        if (stack->capacity > SIZE_MAX / 2) {
            return STACK_CAPACITY_OVERFLOW;
        }

        const size_t new_capacity = stack->capacity * 2;

        if (new_capacity > SIZE_MAX / sizeof(int)) {
            return STACK_CAPACITY_OVERFLOW;
        }

        int* temp = realloc(stack->data, new_capacity * sizeof(int));

        if (temp == NULL) {
            return STACK_MEMORY_ALLOCATION_FAILED;
        }

        stack->capacity = new_capacity;
        stack->data = temp;
    }

    stack->data[stack->top] = data;
    stack->top++;

    return STACK_SUCCESS;
}

StackStatus popStack(Stack* stack) {
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }
    if (stack->top == 0) {
        return STACK_UNDERFLOW;
    }

    stack->top--;

    return STACK_SUCCESS;
}

StackStatus peekStack(const Stack* stack, int* output) {
    if (stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return STACK_INVALID_OUTPUT;
    }
    if (stack->top == 0) {
        return STACK_UNDERFLOW;
    }

    *output = stack->data[stack->top - 1];

    return STACK_SUCCESS;
}

StackStatus destroyStack(Stack** stack) {
    if (stack == NULL || *stack == NULL) {
        return STACK_INVALID_ARGUMENT;
    }

    free((*stack)->data);
    free(*stack);
    *stack = NULL;

    return STACK_SUCCESS;
}