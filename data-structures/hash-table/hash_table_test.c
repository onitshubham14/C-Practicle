#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static size_t string_hash(const void *key)
{
    const unsigned char *str = (const unsigned char *)key;
    size_t hash = 5381;
    int c;
    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) ^ (size_t)c;
    }
    return hash;
}
static size_t constant_hash(const void *key)
{
    (void)key;
    return 0;
}
static int string_equal(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b) == 0;
}
static void test_basic_operations(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    char *key = malloc(6);
    char *value = malloc(6);
    assert(table != NULL);
    assert(key != NULL && value != NULL);
    strcpy(key, "apple");
    strcpy(value, "fruit");
    assert(hash_table_put(table, key, value) == 1);
    assert(hash_table_size(table) == 1);
    assert(hash_table_contains(table, "apple") == 1);
    assert(strcmp((char *)hash_table_get(table, "apple"), "fruit") == 0);
    assert(hash_table_get(table, "missing") == NULL);
    assert(hash_table_remove(table, "apple") == 1);
    assert(hash_table_size(table) == 0);
    assert(hash_table_remove(table, "apple") == 0);
    hash_table_destroy(table);
}
static void test_duplicate_update(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    char *key1 = malloc(4);
    char *value1 = malloc(4);
    char *key2 = malloc(4);
    char *value2 = malloc(4);
    assert(table != NULL);
    assert(key1 && value1 && key2 && value2);
    strcpy(key1, "id1");
    strcpy(value1, "one");
    strcpy(key2, "id1");
    strcpy(value2, "two");
    assert(hash_table_put(table, key1, value1) == 1);
    assert(hash_table_put(table, key2, value2) == 1);
    assert(hash_table_size(table) == 1);
    assert(strcmp((char *)hash_table_get(table, "id1"), "two") == 0);
    hash_table_destroy(table);
}
static void test_collision_handling(void)
{
    HashTable *table = hash_table_create(
        11, constant_hash, string_equal, free, free
    );
    size_t i;
    assert(table != NULL);
    for (i = 0; i < 5; i++) {
        char *key = malloc(16);
        char *value = malloc(16);
        assert(key && value);
        sprintf(key, "key-%lu", (unsigned long)i);
        sprintf(value, "value-%lu", (unsigned long)i);
        assert(hash_table_put(table, key, value) == 1);
    }
    assert(hash_table_size(table) == 5);
    assert(hash_table_collision_count(table) == 4);
    for (i = 0; i < 5; i++) {
        char key[16];
        sprintf(key, "key-%lu", (unsigned long)i);
        assert(hash_table_contains(table, key) == 1);
        assert(hash_table_get(table, key) != NULL);
    }
    printf(
        "Forced collision count: %lu\n",
        (unsigned long)hash_table_collision_count(table)
    );
    assert(hash_table_remove(table, "key-2") == 1);
    assert(hash_table_size(table) == 4);
    assert(hash_table_contains(table, "key-2") == 0);
    assert(hash_table_contains(table, "key-1") == 1);
    assert(hash_table_contains(table, "key-3") == 1);
    assert(hash_table_collision_count(table) == 3);
    hash_table_destroy(table);
}
static void test_growth(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    size_t initial_capacity;
    size_t i;
    assert(table != NULL);
    initial_capacity = hash_table_capacity(table);
    for (i = 0; i < 100; i++) {
        char *key = malloc(32);
        char *value = malloc(32);
        assert(key && value);
        sprintf(key, "growth-key-%lu", (unsigned long)i);
        sprintf(value, "growth-value-%lu", (unsigned long)i);
        assert(hash_table_put(table, key, value) == 1);
    }
    assert(hash_table_size(table) == 100);
    assert(hash_table_capacity(table) > initial_capacity);
    for (i = 0; i < 100; i++) {
        char key[32];
        sprintf(key, "growth-key-%lu", (unsigned long)i);
        assert(hash_table_contains(table, key) == 1);
    }
    hash_table_destroy(table);
}
static void test_reserve(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    size_t old_capacity;
    size_t new_capacity;
    assert(table != NULL);
    old_capacity = hash_table_capacity(table);
    assert(hash_table_reserve(table, 1000) == 1);
    new_capacity = hash_table_capacity(table);
    assert(new_capacity >= 1000);
    assert(new_capacity > old_capacity);
    assert(hash_table_reserve(table, 10) == 1);
    assert(hash_table_capacity(table) == new_capacity);
    hash_table_destroy(table);
}
static void test_shrink(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    size_t large_capacity;
    size_t i;
    assert(table != NULL);
    for (i = 0; i < 200; i++) {
        char *key = malloc(32);
        char *value = malloc(32);
        assert(key && value);
        sprintf(key, "shrink-key-%lu", (unsigned long)i);
        sprintf(value, "shrink-value-%lu", (unsigned long)i);
        assert(hash_table_put(table, key, value) == 1);
    }
    large_capacity = hash_table_capacity(table);
    assert(large_capacity > 11);
    for (i = 0; i < 200; i++) {
        char key[32];
        sprintf(key, "shrink-key-%lu", (unsigned long)i);
        assert(hash_table_remove(table, key) == 1);
    }
    assert(hash_table_size(table) == 0);
    assert(hash_table_capacity(table) < large_capacity);
    assert(hash_table_capacity(table) >= 11);
    hash_table_destroy(table);
}
static void test_large_workload(void)
{
    HashTable *table = hash_table_create(11, string_hash, string_equal, free, free);
    size_t i;
    assert(table != NULL);
    for (i = 0; i < 5000; i++) {
        char *key = malloc(40);
        char *value = malloc(40);
        assert(key && value);
        sprintf(key, "large-key-%lu", (unsigned long)i);
        sprintf(value, "large-value-%lu", (unsigned long)i);
        assert(hash_table_put(table, key, value) == 1);
    }
    assert(hash_table_size(table) == 5000);
    for (i = 0; i < 5000; i += 17) {
        char key[40];
        sprintf(key, "large-key-%lu", (unsigned long)i);
        assert(hash_table_contains(table, key) == 1);
        assert(hash_table_get(table, key) != NULL);
    }
    hash_table_destroy(table);
}
static void test_null_safety(void)
{
    HashTable *table;
    assert(hash_table_create(11, NULL, string_equal, NULL, NULL) == NULL);
    assert(hash_table_create(11, string_hash, NULL, NULL, NULL) == NULL);
    assert(hash_table_size(NULL) == 0);
    assert(hash_table_capacity(NULL) == 0);
    assert(hash_table_load_factor(NULL) == 0.0);
    assert(hash_table_collision_count(NULL) == 0);
    table = hash_table_create(11, string_hash, string_equal, free, free);
    assert(table != NULL);
    assert(hash_table_put(NULL, "key", "value") == 0);
    assert(hash_table_put(table, NULL, "value") == 0);
    assert(hash_table_get(NULL, "key") == NULL);
    assert(hash_table_contains(NULL, "key") == 0);
    assert(hash_table_remove(NULL, "key") == 0);
    assert(hash_table_remove(table, NULL) == 0);
    assert(hash_table_reserve(NULL, 100) == 0);
    assert(hash_table_reserve(table, 0) == 0);
    hash_table_destroy(table);
    hash_table_destroy(NULL);
}
int main(void)
{
    printf("Running hash table tests...\n");
    test_basic_operations();
    printf("[PASS] basic operations\n");
    test_duplicate_update();
    printf("[PASS] duplicate-key update\n");
    test_collision_handling();
    printf("[PASS] collision handling\n");
    test_growth();
    printf("[PASS] automatic growth\n");
    test_reserve();
    printf("[PASS] reserve / rehash\n");
    test_shrink();
    printf("[PASS] automatic shrinking\n");
    test_large_workload();
    printf("[PASS] large workload\n");
    test_null_safety();
    printf("[PASS] null safety\n");
    printf("\nAll hash table tests passed.\n");
    return 0;
}
