#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef int (*priority_queue_compare_fn)(
    const void *a,
    const void *b
);
typedef struct PriorityQueue PriorityQueue;
PriorityQueue *priority_queue_create(
    size_t element_size,
    size_t initial_capacity,
    priority_queue_compare_fn compare
);
void priority_queue_destroy(PriorityQueue *queue);
int priority_queue_enqueue(
    PriorityQueue *queue,
    const void *element
);
int priority_queue_peek(
    const PriorityQueue *queue,
    void *out_element
);
int priority_queue_dequeue(
    PriorityQueue *queue,
    void *out_element
);
int priority_queue_reserve(
    PriorityQueue *queue,
    size_t capacity
);
size_t priority_queue_size(
    const PriorityQueue *queue
);
size_t priority_queue_capacity(
    const PriorityQueue *queue
);
size_t priority_queue_element_size(
    const PriorityQueue *queue
);
int priority_queue_is_empty(
    const PriorityQueue *queue
);
#ifdef __cplusplus
}
#endif
#endif
