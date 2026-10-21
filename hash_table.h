#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdbool.h>

typedef size_t (*HashFunc)(const void *key);
typedef bool (*EqualsFunc)(const void *key1, const void *key2);
typedef void (*FreeFunc)(void *ptr);

typedef struct Node {
    void *key;
    void *value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **buckets;
    size_t num_buckets;
    size_t size;
    HashFunc hash_func;
    EqualsFunc equals_func;
    FreeFunc free_key;
    FreeFunc free_value;
} HashTable;

HashTable *ht_create(size_t initial_buckets, HashFunc hash_func, EqualsFunc equals_func, FreeFunc free_key, FreeFunc free_value);
bool ht_insert(HashTable *ht, void *key, void *value);
void *ht_get(HashTable *ht, const void *key);
bool ht_remove(HashTable *ht, const void *key);
void ht_free(HashTable *ht);

#endif // HASH_TABLE_H