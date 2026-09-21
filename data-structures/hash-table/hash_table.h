#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef size_t (*hash_fn)(const void *key);
typedef int (*key_eq_fn)(const void *a, const void *b);
typedef void (*free_fn)(void *ptr);
typedef struct HashTable HashTable;
/*
 * Creates a hash table.
 *
 * initial_capacity:
 *   Requested number of buckets. The implementation may adjust
 *   this value to a suitable capacity.
 *
 * key_hash:
 *   Function used to calculate the hash of a key.
 *
 * key_equal:
 *   Function used to compare two keys.
 *
 * key_free / value_free:
 *   Optional callbacks used when entries are removed or destroyed.
 *
 * Returns:
 *   A newly allocated hash table, or NULL on allocation failure.
 */
HashTable *hash_table_create(
    size_t initial_capacity,
    hash_fn key_hash,
    key_eq_fn key_equal,
    free_fn key_free,
    free_fn value_free
);
/*
 * Releases the entire hash table and all entries.
 */
void hash_table_destroy(HashTable *table);
/*
 * Inserts a key/value pair.
 *
 * If the key already exists, its associated value is replaced.
 *
 * Returns 1 on success, 0 on allocation failure or invalid input.
 */
int hash_table_put(HashTable *table, void *key, void *value);
/*
 * Retrieves the value associated with a key.
 *
 * Returns the stored value, or NULL when the key does not exist.
 */
void *hash_table_get(const HashTable *table, const void *key);
/*
 * Checks whether a key exists.
 *
 * Returns 1 if present, otherwise 0.
 */
int hash_table_contains(const HashTable *table, const void *key);
/*
 * Removes a key/value pair.
 *
 * Returns 1 if an entry was removed, otherwise 0.
 */
int hash_table_remove(HashTable *table, const void *key);
/*
 * Returns the number of stored entries.
 */
size_t hash_table_size(const HashTable *table);
/*
 * Returns the number of buckets currently allocated.
 */
size_t hash_table_capacity(const HashTable *table);
/*
 * Returns the current load factor:
 *
 *     size / capacity
 */
double hash_table_load_factor(const HashTable *table);
/*
 * Returns the number of collisions currently present.
 *
 * This counts entries sharing buckets with other entries.
 */
size_t hash_table_collision_count(const HashTable *table);
/*
 * Forces the table to resize to at least the requested capacity.
 *
 * Returns 1 on success, 0 on allocation failure or invalid input.
 */
int hash_table_reserve(HashTable *table, size_t capacity);
#ifdef __cplusplus
}
#endif
#endif /* HASH_TABLE_H */
