#ifndef C_DATA_STRUCTURES_DLL_H
#define C_DATA_STRUCTURES_DLL_H

typedef enum {
    DLL_SUCCESS,
    DLL_MEMORY_ALLOCATION_FAILURE,
    DLL_LIST_EMPTY,
    DLL_INVALID_ARGUMENT,
    DLL_INVALID_OUTPUT,
    DLL_CORRUPTED_LIST
} DLLStatus;

typedef struct DoublyLinkedList DoublyLinkedList;

DLLStatus createDLL(DoublyLinkedList** list);
DLLStatus destroyDLL(DoublyLinkedList** list);

DLLStatus pushFrontDLL(DoublyLinkedList* list, int data);
DLLStatus popFrontDLL(DoublyLinkedList* list);
DLLStatus peekFrontDLL(const DoublyLinkedList* list, int* output);

DLLStatus pushBackDLL(DoublyLinkedList* list, int data);
DLLStatus popBackDLL(DoublyLinkedList* list);
DLLStatus peekBackDLL(const DoublyLinkedList* list, int* output);

#endif // C_DATA_STRUCTURES_DLL_H