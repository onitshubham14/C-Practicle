#include "hash_table.h"
#include <stdlib.h>
#define DEFAULT_CAPACITY 11U
#define MIN_CAPACITY 11U
#define MAX_LOAD_FACTOR 0.75
#define MIN_LOAD_FACTOR 0.20
typedef struct HashNode {
    void *key;
    void *value;
    struct HashNode *next;
} HashNode;
struct HashTable {
    HashNode **buckets;
    size_t capacity;
    size_t size;
    hash_fn key_hash;
    key_eq_fn key_equal;
    free_fn key_free;
    free_fn value_free;
};
static int is_prime(size_t n)
{
    size_t divisor;
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (divisor = 3; divisor <= n / divisor; divisor += 2) {
        if (n % divisor == 0) {
            return 0;
        }
    }
    return 1;
}
static size_t next_prime(size_t n)
{
    if (n < 2) {
        return 2;
    }
    if (n % 2 == 0 && n != 2) {
        n++;
    }
    while (!is_prime(n)) {
        n += 2;
    }
    return n;
}
static size_t previous_prime(size_t n)
{
    if (n <= MIN_CAPACITY) {
        return MIN_CAPACITY;
    }
    if (n % 2 == 0) {
        n--;
    }
    while (n > MIN_CAPACITY && !is_prime(n)) {
        n -= 2;
    }
    if (n < MIN_CAPACITY) {
        return MIN_CAPACITY;
    }
    return n;
}
static size_t bucket_index(
    const HashTable *table,
    const void *key
)
{
    return table->key_hash(key) % table->capacity;
}
static void destroy_node(HashTable *table, HashNode *node)
{
    if (table->key_free != NULL) {
        table->key_free(node->key);
    }
    if (table->value_free != NULL) {
        table->value_free(node->value);
    }
    free(node);
}
static HashNode *find_node(
    const HashTable *table,
    const void *key
)
{
    size_t index;
    HashNode *current;
    if (table == NULL || key == NULL) {
        return NULL;
    }
    index = bucket_index(table, key);
    current = table->buckets[index];
    while (current != NULL) {
        if (table->key_equal(current->key, key)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
static int resize_table(HashTable *table, size_t requested_capacity)
{
    HashNode **new_buckets;
    size_t new_capacity;
    size_t i;
    if (table == NULL) {
        return 0;
    }
    new_capacity = next_prime(requested_capacity);
    if (new_capacity == table->capacity) {
        return 1;
    }
    new_buckets = calloc(new_capacity, sizeof(*new_buckets));
    if (new_buckets == NULL) {
        return 0;
    }
    for (i = 0; i < table->capacity; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL) {
            HashNode *next = current->next;
            size_t new_index;
            new_index = table->key_hash(current->key) % new_capacity;
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;
            current = next;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;
    return 1;
}
static int maybe_grow(HashTable *table)
{
    if (hash_table_load_factor(table) > MAX_LOAD_FACTOR) {
        if (table->capacity > (size_t)-1 / 2) {
            return 0;
        }
        return resize_table(table, table->capacity * 2);
    }
    return 1;
}
static void maybe_shrink(HashTable *table)
{
    size_t target;
    if (table == NULL || table->capacity <= MIN_CAPACITY) {
        return;
    }
    if (hash_table_load_factor(table) >= MIN_LOAD_FACTOR) {
        return;
    }
    target = table->capacity / 2;
    if (target < MIN_CAPACITY) {
        target = MIN_CAPACITY;
    }
    target = previous_prime(target);
    if (target < table->capacity) {
        (void)resize_table(table, target);
    }
}
HashTable *hash_table_create(
    size_t initial_capacity,
    hash_fn key_hash,
    key_eq_fn key_equal,
    free_fn key_free,
    free_fn value_free
)
{
    HashTable *table;
    size_t capacity;
    if (key_hash == NULL || key_equal == NULL) {
        return NULL;
    }
    capacity = initial_capacity;
    if (capacity < MIN_CAPACITY) {
        capacity = DEFAULT_CAPACITY;
    }
    capacity = next_prime(capacity);
    table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = calloc(capacity, sizeof(*table->buckets));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->capacity = capacity;
    table->size = 0;
    table->key_hash = key_hash;
    table->key_equal = key_equal;
    table->key_free = key_free;
    table->value_free = value_free;
    return table;
}
void hash_table_destroy(HashTable *table)
{
    size_t i;
    if (table == NULL) {
        return;
    }
    for (i = 0; i < table->capacity; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL) {
            HashNode *next = current->next;
            destroy_node(table, current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}
int hash_table_put(HashTable *table, void *key, void *value)
{
    HashNode *existing;
    HashNode *node;
    size_t index;
    if (table == NULL || key == NULL) {
        return 0;
    }
    existing = find_node(table, key);
    if (existing != NULL) {
        if (table->key_free != NULL) {
            table->key_free(existing->key);
        }
        if (table->value_free != NULL) {
            table->value_free(existing->value);
        }
        existing->key = key;
        existing->value = value;
        return 1;
    }
    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }
    node->key = key;
    node->value = value;
    index = bucket_index(table, key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->size++;
    if (!maybe_grow(table)) {
        /*
         * The entry has already been inserted. The table remains
         * valid even if growing fails because of allocation failure.
         */
        return 1;
    }
    return 1;
}
void *hash_table_get(const HashTable *table, const void *key)
{
    HashNode *node;
    node = find_node(table, key);
    if (node == NULL) {
        return NULL;
    }
    return node->value;
}
int hash_table_contains(const HashTable *table, const void *key)
{
    return find_node(table, key) != NULL;
}
int hash_table_remove(HashTable *table, const void *key)
{
    size_t index;
    HashNode *current;
    HashNode *previous;
    if (table == NULL || key == NULL) {
        return 0;
    }
    index = bucket_index(table, key);
    current = table->buckets[index];
    previous = NULL;
    while (current != NULL) {
        if (table->key_equal(current->key, key)) {
            if (previous == NULL) {
                table->buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }
            destroy_node(table, current);
            table->size--;
            maybe_shrink(table);
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}
size_t hash_table_size(const HashTable *table)
{
    if (table == NULL) {
        return 0;
    }
    return table->size;
}
size_t hash_table_capacity(const HashTable *table)
{
    if (table == NULL) {
        return 0;
    }
    return table->capacity;
}
double hash_table_load_factor(const HashTable *table)
{
    if (table == NULL || table->capacity == 0) {
        return 0.0;
    }
    return (double)table->size / (double)table->capacity;
}
size_t hash_table_collision_count(const HashTable *table)
{
    size_t collisions = 0;
    size_t i;
    if (table == NULL) {
        return 0;
    }
    for (i = 0; i < table->capacity; i++) {
        HashNode *current = table->buckets[i];
        while (current != NULL && current->next != NULL) {
            collisions++;
            current = current->next;
        }
    }
    return collisions;
}
int hash_table_reserve(HashTable *table, size_t capacity)
{
    if (table == NULL || capacity == 0) {
        return 0;
    }
    if (capacity <= table->capacity) {
        return 1;
    }
    return resize_table(table, capacity);
}
