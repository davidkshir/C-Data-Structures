#include <stdlib.h>
#include "DLL.h"

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

struct DoublyLinkedList {
    Node* first;
    Node* last;
};

DLLStatus createDLL(DoublyLinkedList** list) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }
    if (*list != NULL) {
        return DLL_INVALID_OUTPUT;
    }

    DoublyLinkedList* new_list = malloc(sizeof(DoublyLinkedList));
    if (new_list == NULL) {
        return DLL_MEMORY_ALLOCATION_FAILURE;
    }

    new_list->first = NULL;
    new_list->last = NULL;
    *list = new_list;

    return DLL_SUCCESS;
}

DLLStatus destroyDLL(DoublyLinkedList** list) {
    if (list == NULL || *list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }

    if (((*list)->first == NULL) != ((*list)->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    Node* cur = (*list)->first;

    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }

    free(*list);
    *list = NULL;

    return DLL_SUCCESS;
}

DLLStatus pushFrontDLL(DoublyLinkedList* list, const int data) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    Node* new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return DLL_MEMORY_ALLOCATION_FAILURE;
    }

    new_node->data = data;
    new_node->next = list->first;
    new_node->prev = NULL;

    if (list->first == NULL) {
        list->last = new_node;
    }
    else {
        list->first->prev = new_node;
    }

    list->first = new_node;

    return DLL_SUCCESS;
}

DLLStatus popFrontDLL(DoublyLinkedList* list) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    if (list->first == NULL) {
        return DLL_LIST_EMPTY;
    }

    Node* temp = list->first;

    if (list->first->next == NULL) {
        list->first = NULL;
        list->last = NULL;
    }
    else {
        list->first = list->first->next;
        list->first->prev = NULL;
    }

    free(temp);

    return DLL_SUCCESS;
}

DLLStatus peekFrontDLL(const DoublyLinkedList* list, int* output) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return DLL_INVALID_OUTPUT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    if (list->first == NULL) {
        return DLL_LIST_EMPTY;
    }

    *output = list->first->data;

    return DLL_SUCCESS;
}

DLLStatus pushBackDLL(DoublyLinkedList* list, const int data) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    Node* new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return DLL_MEMORY_ALLOCATION_FAILURE;
    }

    new_node->data = data;
    new_node->prev = list->last;
    new_node->next = NULL;

    if (list->last == NULL) {
        list->first = new_node;
    }
    else {
        list->last->next = new_node;
    }

    list->last = new_node;

    return DLL_SUCCESS;
}

DLLStatus popBackDLL(DoublyLinkedList* list) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    if (list->first == NULL) {
        return DLL_LIST_EMPTY;
    }

    Node* temp = list->last;

    if (list->last->prev == NULL) {
        list->first = NULL;
        list->last = NULL;
    }
    else {
        temp->prev->next = NULL;
        list->last = temp->prev;
    }

    free(temp);

    return DLL_SUCCESS;
}

DLLStatus peekBackDLL(const DoublyLinkedList* list, int* output) {
    if (list == NULL) {
        return DLL_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return DLL_INVALID_OUTPUT;
    }

    if ((list->first == NULL) != (list->last == NULL)) {
        return DLL_CORRUPTED_LIST;
    }

    if (list->last == NULL) {
        return DLL_LIST_EMPTY;
    }

    *output = list->last->data;

    return DLL_SUCCESS;
}