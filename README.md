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
