# C Data Structures

A collection of data structures implemented from scratch in C to explore
manual memory management, pointers, data storage, and low-level
data structure design.

## Hash Table

A dynamically resizing hash table using string keys and generic `void*`
values.

### Features

- 64-bit FNV-1a hashing
- Separate chaining for collision handling
- Automatic resizing at a 0.75 load factor
- Generic value storage using `void*`
- Copies and owns inserted keys and values
- Cached hashes for faster collision-chain searches
- Duplicate-key detection
- Explicit error handling through `HashTableStatus`

### Example

```c
HashTable* table = NULL;
createHashTable(16, &table);

int value = 42;
hashTableInsertion(table, "answer", &value, sizeof(value));

const void* output = NULL;

if (searchHashTable(table, "answer", &output) == HASH_TABLE_SUCCESS) {
    printf("%d\n", *(const int*)output);
}

hashTableDeletion(table, "answer");
destroyHashTable(&table);
```

Values are copied into table-owned memory during insertion. Search returns a
read-only pointer to the stored value, so the caller is responsible for
casting it back to the appropriate type.

### Implementation

Each bucket contains a singly linked list of entries for collision resolution.
New entries are inserted at the head of their chain.

The table automatically doubles its bucket count when an insertion would
reach a load factor of 0.75. Existing entries are redistributed using their
cached hashes without reallocating their keys or values.

### Complexity 

With a well-distributed hash function and reasonable load factor:

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Search    | O(1)    | O(n)       |
| Insert    | O(1)*   | O(n)       |
| Delete    | O(1)    | O(n)       |

Insertion is amortized O(1). Individual insertions that trigger resizing
require O(n) work to redistribute existing entries.

The worst case occurs when many keys collide into the same bucket.

### Memory Management

The table owns separate allocations for each entry's key and value. Deletion
releases these allocations, while `destroyHashTable()` releases all remaining
entries, the bucket array, and the table itself.

## Singly Linked List

An integer singly linked list with an opaque public interface and privately managed nodes.

### Features

- Front and back insertion
- Front and back removal
- Front and back peek operations
- Explicit error handling through `SLLStatus`
- Copies peeked values into caller-provided memory

### Example

```c
SinglyLinkedList* list = NULL;
createList(&list);

pushBack(list, 10);
pushBack(list, 20);
pushFront(list, 5);

int value;

if (peekFront(list, &value) == SLL_SUCCESS) {
    printf("%d\n", value);
}

popFront(list);
destroyList(&list);
```

Peek operations copy the stored integer into a caller-provided output variable,
preventing internal node memory from being exposed.

### Implementation

Each node stores an integer and a pointer to the next node in the list.
The list maintains a pointer to its first node, while node structures remain
private to the implementation.

Front operations access the first node directly, while back operations traverse
the list to locate its final node.

### Complexity

| Operation  | Time |
|------------|------|
| Push Front | O(1) |
| Pop Front  | O(1) |
| Peek Front | O(1) |
| Push Back  | O(n) |
| Pop Back   | O(n) |
| Peek Back  | O(n) |

## Doubly Linked List

An integer doubly linked list that maintains pointers to both ends of the list, with an opaque public interface and privately managed nodes.

### Features

- Front and back insertion
- Front and back removal
- Front and back peek operations
- Private node implementation
- Explicit error handling through `DLLStatus`
- Internal endpoint consistency checks

### Example

```c
DoublyLinkedList* list = NULL;
createDLL(&list);

pushBackDLL(list, 10);
pushBackDLL(list, 20);
pushFrontDLL(list, 5);

int value;

if (peekFrontDLL(list, &value) == DLL_SUCCESS) {
    printf("%d\n", value);
}

popBackDLL(list);
destroyDLL(&list);
```

Peek operations copy the stored integer into a caller-provided output variable rather than exposing internal node memory.

### Implementation

Each node stores an integer and pointers to both the next and previous nodes. The list maintains pointers to its first and last nodes, allowing operations at either end without traversing the list.

The implementation maintains the invariant that the first and last pointers are either both valid or both `NULL`, allowing inconsistent endpoint states to be detected.

### Complexity

| Operation  | Time |
|------------|------|
| Push Front | O(1) |
| Pop Front  | O(1) |
| Peek Front | O(1) |
| Push Back  | O(1) |
| Pop Back   | O(1) |
| Peek Back  | O(1) |

## Stack

A dynamically resizing integer stack backed by a contiguous array, providing LIFO storage with automatic capacity growth.

### Features

- LIFO push, pop, and peek operations
- Dynamically resizing array-backed storage
- Automatic capacity doubling
- Amortized constant-time push
- Opaque `Stack` type
- Explicit error handling through `StackStatus`
- Capacity overflow protection

### Example

```c
Stack* stack = NULL;
createStack(&stack);

pushStack(stack, 10);
pushStack(stack, 20);
pushStack(stack, 30);

int value;

if (peekStack(stack, &value) == STACK_SUCCESS) {
    printf("%d\n", value);
}

popStack(stack);
destroyStack(&stack);
```

Peek copies the top integer into a caller-provided output variable without removing it or exposing the stack's internal storage.

### Implementation

The stack stores integers in a contiguous dynamically allocated array. When the array reaches capacity, its capacity is doubled and the existing allocation is resized using `realloc()`.

The stack tracks the next available position in the array, allowing push, pop, and peek operations without searching or shifting elements.

### Complexity

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Push      | O(1)*   | O(n)       |
| Pop       | O(1)    | O(1)       |
| Peek      | O(1)    | O(1)       |

Push is amortized O(1). An individual push that triggers a resize requires O(n) work to resize and preserve the existing elements.
## Dynamic Array

A dynamically resizing integer array with indexed access and constant-time unordered removal.

### Features

- Dynamic integer storage
- Indexed element access
- Automatic capacity doubling
- Amortized constant-time insertion
- Constant-time unordered removal
- Opaque `DynamicArray` type
- Explicit error handling through `DynamicArrayStatus`
- Capacity overflow protection

### Example

```c
DynamicArray* array = NULL;
createDynamicArray(&array);

addDynamicArray(array, 10);
addDynamicArray(array, 20);
addDynamicArray(array, 30);

int value;

if (getDynamicArray(array, 1, &value) == DYNAMIC_ARRAY_SUCCESS) {
    printf("%d\n", value);
}

removeDynamicArray(array, 1);
destroyDynamicArray(&array);
```

Element access copies the integer at the requested index into a caller-provided output variable without exposing the array's internal storage.

### Implementation

The array stores integers in a contiguous dynamically allocated block of memory. When the array reaches capacity, its capacity is doubled using `realloc()` while preserving the existing elements.

Removal does not preserve element order. Instead of shifting subsequent elements, the final element is moved into the removed element's position, allowing removal by index in constant time.

### Complexity

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Add       | O(1)*   | O(n)       |
| Get       | O(1)    | O(1)       |
| Remove    | O(1)    | O(1)       |

Addition is amortized O(1). An individual addition that triggers a resize requires O(n) work to resize and preserve the existing elements.