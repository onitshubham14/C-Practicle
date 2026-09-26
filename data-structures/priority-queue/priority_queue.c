#include "priority_queue.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MIN_CAPACITY 8
struct PriorityQueue {
    unsigned char *data;
    size_t size;
    size_t capacity;
    size_t element_size;
    priority_queue_compare_fn compare;
};
static int mul_overflow(size_t a, size_t b)
{
    return b != 0 && a > SIZE_MAX / b;
}
static int valid(const PriorityQueue *queue)
{
    return queue != NULL &&
           queue->element_size != 0 &&
           queue->compare != NULL;
}
static unsigned char *at(
    PriorityQueue *queue,
    size_t index
)
{
    return queue->data + index * queue->element_size;
}
static const unsigned char *at_const(
    const PriorityQueue *queue,
    size_t index
)
{
    return queue->data + index * queue->element_size;
}
static void swap_elements(
    PriorityQueue *queue,
    size_t first,
    size_t second
)
{
    if (first == second) {
        return;
    }
    unsigned char temp[queue->element_size];
    unsigned char *a = at(queue, first);
    unsigned char *b = at(queue, second);
    memcpy(temp, a, queue->element_size);
    memcpy(a, b, queue->element_size);
    memcpy(b, temp, queue->element_size);
}
static int resize(
    PriorityQueue *queue,
    size_t capacity
)
{
    if (!valid(queue) ||
        capacity == 0 ||
        capacity < queue->size ||
        mul_overflow(capacity, queue->element_size)) {
        return 0;
    }
    if (capacity == queue->capacity) {
        return 1;
    }
    unsigned char *data = realloc(
        queue->data,
        capacity * queue->element_size
    );
    if (data == NULL) {
        return 0;
    }
    queue->data = data;
    queue->capacity = capacity;
    return 1;
}
static int grow(PriorityQueue *queue)
{
    if (queue->size < queue->capacity) {
        return 1;
    }
    if (queue->capacity > SIZE_MAX / 2) {
        return 0;
    }
    size_t new_capacity =
        queue->capacity == 0
            ? MIN_CAPACITY
            : queue->capacity * 2;
    return resize(queue, new_capacity);
}
static void sift_up(
    PriorityQueue *queue,
    size_t index
)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (queue->compare(
                at(queue, index),
                at(queue, parent)
            ) >= 0) {
            break;
        }
        swap_elements(queue, index, parent);
        index = parent;
    }
}
static void sift_down(
    PriorityQueue *queue,
    size_t index
)
{
    while (1) {
        size_t left = index * 2 + 1;
        size_t right = index * 2 + 2;
        size_t highest_priority = index;
        if (left < queue->size &&
            queue->compare(
                at(queue, left),
                at(queue, highest_priority)
            ) < 0) {
            highest_priority = left;
        }
        if (right < queue->size &&
            queue->compare(
                at(queue, right),
                at(queue, highest_priority)
            ) < 0) {
            highest_priority = right;
        }
        if (highest_priority == index) {
            break;
        }
        swap_elements(
            queue,
            index,
            highest_priority
        );
        index = highest_priority;
    }
}
PriorityQueue *priority_queue_create(
    size_t element_size,
    size_t initial_capacity,
    priority_queue_compare_fn compare
)
{
    if (element_size == 0 || compare == NULL) {
        return NULL;
    }
    if (initial_capacity < MIN_CAPACITY) {
        initial_capacity = MIN_CAPACITY;
    }
    if (mul_overflow(initial_capacity, element_size)) {
        return NULL;
    }
    PriorityQueue *queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->data = malloc(
        initial_capacity * element_size
    );
    if (queue->data == NULL) {
        free(queue);
        return NULL;
    }
    queue->size = 0;
    queue->capacity = initial_capacity;
    queue->element_size = element_size;
    queue->compare = compare;
    return queue;
}
void priority_queue_destroy(PriorityQueue *queue)
{
    if (queue == NULL) {
        return;
    }
    free(queue->data);
    free(queue);
}
int priority_queue_enqueue(
    PriorityQueue *queue,
    const void *element
)
{
    if (!valid(queue) || element == NULL) {
        return 0;
    }
    if (!grow(queue)) {
        return 0;
    }
    memcpy(
        at(queue, queue->size),
        element,
        queue->element_size
    );
    queue->size++;
    sift_up(queue, queue->size - 1);
    return 1;
}
int priority_queue_peek(
    const PriorityQueue *queue,
    void *out_element
)
{
    if (!valid(queue) ||
        queue->size == 0 ||
        out_element == NULL) {
        return 0;
    }
    memcpy(
        out_element,
        at_const(queue, 0),
        queue->element_size
    );
    return 1;
}
int priority_queue_dequeue(
    PriorityQueue *queue,
    void *out_element
)
{
    if (!valid(queue) || queue->size == 0) {
        return 0;
    }
    if (out_element != NULL) {
        memcpy(
            out_element,
            at(queue, 0),
            queue->element_size
        );
    }
    queue->size--;
    if (queue->size > 0) {
        memcpy(
            at(queue, 0),
            at(queue, queue->size),
            queue->element_size
        );
        sift_down(queue, 0);
    }
    return 1;
}
int priority_queue_reserve(
    PriorityQueue *queue,
    size_t capacity
)
{
    if (!valid(queue)) {
        return 0;
    }
    if (capacity <= queue->capacity) {
        return 1;
    }
    return resize(queue, capacity);
}
size_t priority_queue_size(
    const PriorityQueue *queue
)
{
    return valid(queue) ? queue->size : 0;
}
size_t priority_queue_capacity(
    const PriorityQueue *queue
)
{
    return valid(queue) ? queue->capacity : 0;
}
size_t priority_queue_element_size(
    const PriorityQueue *queue
)
{
    return valid(queue) ? queue->element_size : 0;
}
int priority_queue_is_empty(
    const PriorityQueue *queue
)
{
    return !valid(queue) || queue->size == 0;
}
