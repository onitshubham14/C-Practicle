#include "dynamic_array.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static void test_push_and_get(void)
{
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        2,
        NULL
    );
    assert(array != NULL);
    assert(dynamic_array_size(array) == 0);
    assert(dynamic_array_capacity(array) >= 8);
    for (int i = 0; i < 1000; ++i) {
        assert(dynamic_array_push(array, &i) == 1);
    }
    assert(dynamic_array_size(array) == 1000);
    for (int i = 0; i < 1000; ++i) {
        int *value = dynamic_array_get(array, (size_t)i);
        assert(value != NULL);
        assert(*value == i);
    }
    dynamic_array_destroy(array);
}
static void test_insert_and_remove(void)
{
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        8,
        NULL
    );
    assert(array != NULL);
    for (int i = 1; i <= 5; ++i) {
        assert(dynamic_array_push(array, &i) == 1);
    }
    int value = 99;
    assert(dynamic_array_insert(array, 2, &value) == 1);
    assert(dynamic_array_size(array) == 6);
    assert(*(int *)dynamic_array_get(array, 2) == 99);
    assert(*(int *)dynamic_array_get(array, 3) == 3);
    int removed = 0;
    assert(dynamic_array_remove(array, 2, &removed) == 1);
    assert(removed == 99);
    assert(dynamic_array_size(array) == 5);
    assert(*(int *)dynamic_array_get(array, 2) == 3);
    dynamic_array_destroy(array);
}
static void test_pop(void)
{
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        8,
        NULL
    );
    assert(array != NULL);
    int value = 42;
    assert(dynamic_array_push(array, &value) == 1);
    assert(dynamic_array_size(array) == 1);
    int popped = 0;
    assert(dynamic_array_pop(array, &popped) == 1);
    assert(popped == 42);
    assert(dynamic_array_size(array) == 0);
    assert(dynamic_array_pop(array, &popped) == 0);
    dynamic_array_destroy(array);
}
static void test_reserve_and_shrink(void)
{
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        8,
        NULL
    );
    assert(array != NULL);
    assert(dynamic_array_reserve(array, 1024) == 1);
    assert(dynamic_array_capacity(array) >= 1024);
    int value = 7;
    for (int i = 0; i < 10; ++i) {
        assert(dynamic_array_push(array, &value) == 1);
    }
    assert(dynamic_array_shrink_to_fit(array) == 1);
    assert(dynamic_array_capacity(array) == 10);
    dynamic_array_destroy(array);
}
static int freed_count = 0;
static void count_free(void *element)
{
    if (element != NULL) {
        freed_count++;
    }
}
static void test_clear_and_destructor(void)
{
    freed_count = 0;
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        8,
        count_free
    );
    assert(array != NULL);
    int value = 123;
    for (int i = 0; i < 5; ++i) {
        assert(dynamic_array_push(array, &value) == 1);
    }
    assert(dynamic_array_clear(array) == 1);
    assert(dynamic_array_size(array) == 0);
    assert(freed_count == 5);
    for (int i = 0; i < 3; ++i) {
        assert(dynamic_array_push(array, &value) == 1);
    }
    dynamic_array_destroy(array);
    assert(freed_count == 8);
}
static void test_invalid_operations(void)
{
    DynamicArray *array = dynamic_array_create(
        sizeof(int),
        8,
        NULL
    );
    assert(array != NULL);
    int value = 1;
    assert(dynamic_array_push(NULL, &value) == 0);
    assert(dynamic_array_push(array, NULL) == 0);
    assert(dynamic_array_pop(NULL, NULL) == 0);
    assert(dynamic_array_remove(array, 0, NULL) == 0);
    assert(dynamic_array_insert(array, 1, &value) == 0);
    assert(dynamic_array_get(array, 0) == NULL);
    assert(dynamic_array_reserve(NULL, 100) == 0);
    assert(dynamic_array_shrink_to_fit(NULL) == 0);
    assert(dynamic_array_clear(NULL) == 0);
    dynamic_array_destroy(array);
    dynamic_array_destroy(NULL);
}
int main(void)
{
    test_push_and_get();
    test_insert_and_remove();
    test_pop();
    test_reserve_and_shrink();
    test_clear_and_destructor();
    test_invalid_operations();
    printf("All dynamic array tests passed.\n");
    return 0;
}
