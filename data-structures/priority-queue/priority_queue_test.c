#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
static int int_compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}
static int max_int_compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}
static void test_basic_operations(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        4,
        int_compare
    );
    assert(queue != NULL);
    assert(priority_queue_is_empty(queue));
    assert(priority_queue_size(queue) == 0);
    assert(priority_queue_capacity(queue) >= 8);
    int values[] = {40, 10, 30, 5, 20};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        assert(priority_queue_enqueue(queue, &values[i]) == 1);
    }
    assert(priority_queue_size(queue) == 5);
    int top = 0;
    assert(priority_queue_peek(queue, &top) == 1);
    assert(top == 5);
    assert(priority_queue_size(queue) == 5);
    priority_queue_destroy(queue);
}
static void test_priority_order(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        int_compare
    );
    assert(queue != NULL);
    int values[] = {
        50, 10, 40, 20, 30,
        5, 90, 1, 70
    };
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        assert(priority_queue_enqueue(queue, &values[i]) == 1);
    }
    int expected[] = {
        1, 5, 10, 20, 30,
        40, 50, 70, 90
    };
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        int actual = 0;
        assert(priority_queue_dequeue(queue, &actual) == 1);
        assert(actual == expected[i]);
    }
    assert(priority_queue_is_empty(queue));
    priority_queue_destroy(queue);
}
static void test_max_priority(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        max_int_compare
    );
    assert(queue != NULL);
    int values[] = {10, 50, 20, 40, 30};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        assert(priority_queue_enqueue(queue, &values[i]) == 1);
    }
    int expected[] = {50, 40, 30, 20, 10};
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        int actual = 0;
        assert(priority_queue_dequeue(queue, &actual) == 1);
        assert(actual == expected[i]);
    }
    priority_queue_destroy(queue);
}
static void test_duplicates_and_negative_values(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        int_compare
    );
    assert(queue != NULL);
    int values[] = {
        -10, 5, -10, 0, 5,
        -100, 50, -1, 0
    };
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        assert(priority_queue_enqueue(queue, &values[i]) == 1);
    }
    int expected[] = {
        -100, -10, -10, -1,
        0, 0, 5, 5, 50
    };
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        int actual = 0;
        assert(priority_queue_dequeue(queue, &actual) == 1);
        assert(actual == expected[i]);
    }
    priority_queue_destroy(queue);
}
static void test_large_workload(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        int_compare
    );
    assert(queue != NULL);
    for (int i = 10000; i >= 1; --i) {
        assert(priority_queue_enqueue(queue, &i) == 1);
    }
    assert(priority_queue_size(queue) == 10000);
    assert(priority_queue_capacity(queue) >= 10000);
    for (int expected = 1; expected <= 10000; ++expected) {
        int actual = 0;
        assert(priority_queue_dequeue(queue, &actual) == 1);
        assert(actual == expected);
    }
    assert(priority_queue_is_empty(queue));
    priority_queue_destroy(queue);
}
static void test_reserve(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        int_compare
    );
    assert(queue != NULL);
    assert(priority_queue_reserve(queue, 2048) == 1);
    assert(priority_queue_capacity(queue) >= 2048);
    int value = 123;
    assert(priority_queue_enqueue(queue, &value) == 1);
    int top = 0;
    assert(priority_queue_peek(queue, &top) == 1);
    assert(top == 123);
    priority_queue_destroy(queue);
}
static void test_invalid_operations(void)
{
    PriorityQueue *queue = priority_queue_create(
        sizeof(int),
        8,
        int_compare
    );
    assert(queue != NULL);
    int value = 10;
    int output = 0;
    assert(priority_queue_enqueue(NULL, &value) == 0);
    assert(priority_queue_enqueue(queue, NULL) == 0);
    assert(priority_queue_peek(NULL, &output) == 0);
    assert(priority_queue_peek(queue, NULL) == 0);
    assert(priority_queue_dequeue(NULL, &output) == 0);
    assert(priority_queue_reserve(NULL, 100) == 0);
    assert(priority_queue_dequeue(queue, &output) == 0);
    assert(priority_queue_is_empty(queue));
    assert(priority_queue_create(0, 8, int_compare) == NULL);
    assert(priority_queue_create(sizeof(int), 8, NULL) == NULL);
    priority_queue_destroy(queue);
    priority_queue_destroy(NULL);
}
int main(void)
{
    test_basic_operations();
    test_priority_order();
    test_max_priority();
    test_duplicates_and_negative_values();
    test_large_workload();
    test_reserve();
    test_invalid_operations();
    printf("All priority queue tests passed.\n");
    return 0;
}
