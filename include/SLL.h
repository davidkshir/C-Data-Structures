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

SLLStatus createList(SinglyLinkedList** list);
SLLStatus destroyList(SinglyLinkedList** list);
SLLStatus pushFront(SinglyLinkedList* list, int data);
SLLStatus popFront(SinglyLinkedList* list);
SLLStatus pushBack(SinglyLinkedList* list, int data);
SLLStatus popBack(SinglyLinkedList* list);
SLLStatus peekFront(const SinglyLinkedList* list, int* output);
SLLStatus peekBack(const SinglyLinkedList* list, int* output);

#endif //C_DATA_STRUCTURES_SLL_H
