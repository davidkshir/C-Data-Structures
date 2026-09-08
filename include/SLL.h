#ifndef C_DATA_STRUCTURES_SLL_H
#define C_DATA_STRUCTURES_SLL_H

typedef enum{
    SLL_SUCCESS,
    SLL_MEMORY_ALLOCATION_FAILURE,
    SLL_LIST_EMPTY,
    SLL_INVALID_ARGUMENT,
    SLL_INVALID_OUTPUT
}SLLStatus;

typedef struct SinglyLinkedList SinglyLinkedList;

SLLStatus createSLL(SinglyLinkedList** list);
SLLStatus destroySLL(SinglyLinkedList** list);

SLLStatus pushFrontSLL(SinglyLinkedList* list, int data);
SLLStatus popFrontSLL(SinglyLinkedList* list);
SLLStatus peekFrontSLL(const SinglyLinkedList* list, int* output);

SLLStatus pushBackSLL(SinglyLinkedList* list, int data);
SLLStatus popBackSLL(SinglyLinkedList* list);
SLLStatus peekBackSLL(const SinglyLinkedList* list, int* output);

#endif //C_DATA_STRUCTURES_SLL_H
