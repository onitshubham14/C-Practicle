_#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define DEFAULT_INITIAL_BUCKETS 16
#define LOAD_FACTOR_THRESHOLD 0.75

HashTable *ht_create(size_t initial_buckets, HashFunc hash_func, EqualsFunc equals_func, FreeFunc free_key, FreeFunc free_value) {
    if (!hash_func || !equals_func) return NULL;

    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->num_buckets = initial_buckets > 0 ? initial_buckets : DEFAULT_INITIAL_BUCKETS;
    ht->size = 0;
    ht->hash_func = hash_func;
    ht->equals_func = equals_func;
    ht->free_key = free_key;
    ht->free_value = free_value;

    ht->buckets = (Node **)calloc(ht->num_buckets, sizeof(Node *));
    if (!ht->buckets) {
        free(ht);
        return NULL;
    }

    return ht;
}

static void ht_rehash(HashTable *ht) {
    size_t new_num_buckets = ht->num_buckets * 2;
    Node **new_buckets = (Node **)calloc(new_num_buckets, sizeof(Node *));
    if (!new_buckets) return;

    for (size_t i = 0; i < ht->num_buckets; i++) {
        Node *curr = ht->buckets[i];
        while (curr) {
            Node *next = curr->next;
            size_t new_index = ht->hash_func(curr->key) % new_num_buckets;

            curr->next = new_buckets[new_index];
            new_buckets[new_index] = curr;

            curr = next;
        }
    }

    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->num_buckets = new_num_buckets;
}

bool ht_insert(HashTable *ht, void *key, void *value) {
    if (!ht) return false;

    // Rehash if adding a new element causes load factor > 0.75
    if ((double)(ht->size + 1) / ht->num_buckets > LOAD_FACTOR_THRESHOLD) {
        ht_rehash(ht);
    }

    size_t index = ht->hash_func(key) % ht->num_buckets;
    Node *curr = ht->buckets[index];

    // Check for duplicate key updates
    while (curr) {
        if (ht->equals_func(curr->key, key)) {
            if (ht->free_value) {
                ht->free_value(curr->value);
            }
            if (ht->free_key && curr->key != key) {
                ht->free_key(key);
            }
            curr->value = value;
            return true;
        }
        curr = curr->next;
    }

    // Insert new node into chain
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    ht->size++;

    return true;
}

void *ht_get(HashTable *ht, const void *key) {
    if (!ht) return NULL;

    size_t index = ht->hash_func(key) % ht->num_buckets;
    Node *curr = ht->buckets[index];

    while (curr) {
        if (ht->equals_func(curr->key, key)) {
            return curr->value;
        }
        curr = curr->next;
    }

    return NULL;
}

bool ht_remove(HashTable *ht, const void *key) {
    if (!ht) return false;

    size_t index = ht->hash_func(key) % ht->num_buckets;
    Node *curr = ht->buckets[index];
    Node *prev = NULL;

    while (curr) {
        if (ht->equals_func(curr->key, key)) {
            if (prev) {
                prev->next = curr->next;
            } else {
                ht->buckets[index] = curr->next;
            }

            if (ht->free_key) ht->free_key(curr->key);
            if (ht->free_value) ht->free_value(curr->value);

            free(curr);
            ht->size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;
}

void ht_free(HashTable *ht) {
    if (!ht) return;

    for (size_t i = 0; i < ht->num_buckets; i++) {
        Node *curr = ht->buckets[i];
        while (curr) {
            Node *next = curr->next;
            if (ht->free_key) ht->free_key(curr->key);
            if (ht->free_value) ht->free_value(curr->value);
            free(curr);
            curr = next;
        }
    }

    free(ht->buckets);
    free(ht);
}