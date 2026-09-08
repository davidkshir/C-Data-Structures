#ifndef C_DATA_STRUCTURES_STACK_H
#define C_DATA_STRUCTURES_STACK_H

typedef enum {
    STACK_SUCCESS,
    STACK_UNDERFLOW,
    STACK_MEMORY_ALLOCATION_FAILED,
    STACK_INVALID_ARGUMENT,
    STACK_INVALID_OUTPUT,
    STACK_CAPACITY_OVERFLOW
} StackStatus;

typedef struct Stack Stack;

StackStatus createStack(Stack** stack);
StackStatus destroyStack(Stack** stack);

StackStatus pushStack(Stack* stack, int data);
StackStatus popStack(Stack* stack);
StackStatus peekStack(const Stack* stack, int* output);

#endif //C_DATA_STRUCTURES_STACK_H
