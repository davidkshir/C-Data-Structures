#include <stdlib.h>
#include "SLL.h"

typedef struct Node {
    struct Node* next_node;
    int data;
}Node;

struct SinglyLinkedList {
    Node* first_node;
};

SLLStatus createList(SinglyLinkedList** list){
    if (list == NULL){
        return SLL_INVALID_ARGUMENT;
    }
    if (*list != NULL) {
        return SLL_INVALID_OUTPUT;
    }

    SinglyLinkedList *new_list = malloc(sizeof(SinglyLinkedList));
    if (new_list == NULL) {
        return SLL_MEMORY_ALLOCATION_FAILURE;
    }

    new_list->first_node = NULL;
    *list = new_list;

    return SLL_SUCCESS;
}

SLLStatus destroyList(SinglyLinkedList** list){
    if (list == NULL || *list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }

    Node* next = NULL;
    Node* cur = (*list)->first_node;

    while (cur != NULL) {
        next = cur->next_node;
        free(cur);
        cur = next;
    }
    free(*list);
    *list = NULL;

    return SLL_SUCCESS;
}

SLLStatus pushFront(SinglyLinkedList* list, const int data) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        return SLL_MEMORY_ALLOCATION_FAILURE;
    }

    new_node->next_node = list->first_node;
    new_node->data = data;
    list->first_node = new_node;


    return SLL_SUCCESS;
}

SLLStatus popFront(SinglyLinkedList* list) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }
    if (list->first_node == NULL) {
        return SLL_LIST_EMPTY;
    }

    Node *temp = list->first_node;
    list->first_node = list->first_node->next_node;
    free(temp);
    return SLL_SUCCESS;
}

SLLStatus pushBack(SinglyLinkedList* list, const int data) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return SLL_MEMORY_ALLOCATION_FAILURE;
    }
    new_node->data = data;
    new_node->next_node = NULL;

    if(list->first_node == NULL){
        list->first_node = new_node;
        return SLL_SUCCESS;
    }

    Node *current = list->first_node;

    while (current->next_node != NULL){
        current = current->next_node;
    }

    current->next_node = new_node;

    return SLL_SUCCESS;
}

SLLStatus popBack(SinglyLinkedList* list) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }

    if (list->first_node == NULL) {
        return SLL_LIST_EMPTY;
    }

    Node *current = list->first_node;
    Node *previous = NULL;

    while (current->next_node != NULL){
        previous = current;
        current = current->next_node;
    }

    if (previous == NULL){
        list->first_node = NULL;
    }
    else{
        previous->next_node = NULL;
    }

    free(current);

    return SLL_SUCCESS;
}

SLLStatus peekFront(const SinglyLinkedList* list, int* output) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return SLL_INVALID_OUTPUT;
    }
    if (list->first_node == NULL) {
        return SLL_LIST_EMPTY;
    }

    *output = list->first_node->data;

    return SLL_SUCCESS;
}

SLLStatus peekBack(const SinglyLinkedList* list, int* output) {
    if (list == NULL) {
        return SLL_INVALID_ARGUMENT;
    }
    if (output == NULL) {
        return SLL_INVALID_OUTPUT;
    }
    if (list->first_node == NULL) {
        return SLL_LIST_EMPTY;
    }

    const Node* cur = list->first_node;

    while (cur->next_node != NULL) {
        cur = cur->next_node;
    }

    *output = cur->data;

    return SLL_SUCCESS;
}