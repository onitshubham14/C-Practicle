# Generic Priority Queue

A generic, dynamically growing priority queue implementation in C11 backed by an array-based binary heap.

## Features

- Generic element storage using `element_size`
- Custom comparator support
- Configurable priority ordering
- Dynamic capacity growth
- Enqueue, peek, and dequeue operations
- Explicit capacity reservation
- Overflow-safe memory allocation
- Allocation failure handling
- Duplicate and negative values supported
- C11 compatible
- No external dependencies

## How Priority Works

The comparator determines which element has higher priority.

For example, an ascending integer comparator:

`return (x > y) - (x < y);`

causes the smallest value to be dequeued first.

A descending comparator can instead make the largest value have the highest priority.

## API

### Create

`PriorityQueue *priority_queue_create(size_t element_size, size_t initial_capacity, priority_queue_compare_fn compare);`

Creates an empty priority queue.

### Enqueue

`int priority_queue_enqueue(PriorityQueue *queue, const void *element);`

Adds an element while maintaining the priority ordering.

### Peek

`int priority_queue_peek(const PriorityQueue *queue, void *out_element);`

Copies the highest-priority element without removing it.

### Dequeue

`int priority_queue_dequeue(PriorityQueue *queue, void *out_element);`

Removes the highest-priority element and optionally copies it into `out_element`.

### Reserve

`int priority_queue_reserve(PriorityQueue *queue, size_t capacity);`

Ensures that the queue has at least the requested capacity.

### Queries

`size_t priority_queue_size(const PriorityQueue *queue);`

`size_t priority_queue_capacity(const PriorityQueue *queue);`

`size_t priority_queue_element_size(const PriorityQueue *queue);`

`int priority_queue_is_empty(const PriorityQueue *queue);`

### Destroy

`void priority_queue_destroy(PriorityQueue *queue);`

Releases all memory owned by the priority queue.

## Complexity

For `n` elements and element size `s`:

| Operation | Complexity |
|---|---|
| Enqueue | O(log n * s) |
| Peek | O(s) |
| Dequeue | O(log n * s) |
| Reserve | O(n * s) when reallocation occurs |
| Size | O(1) |
| Is Empty | O(1) |

## Implementation

The queue uses an array-based binary heap.

For an element at index `i`:

- Parent: `(i - 1) / 2`
- Left child: `2 * i + 1`
- Right child: `2 * i + 2`

### Sift-Up

When an element is enqueued, it is inserted at the end and moved upward until the priority ordering is restored.

### Sift-Down

When the highest-priority element is dequeued, the final element is moved to the root and pushed downward until the priority ordering is restored.

## Building and Testing

Compile with GCC:

`gcc -std=c11 -Wall -Wextra -Wpedantic priority_queue.c priority_queue_test.c -o priority_queue_test`

Run:

`./priority_queue_test`

Expected output:

`All priority queue tests passed.

## Test Coverage

The test suite covers:

- Basic enqueue and peek operations
- Priority-ordered dequeue
- Custom maximum-priority ordering
- Duplicate values
- Negative values
- 10,000-element workload
- Capacity reservation
- Empty queue behavior
- Invalid and null operations
- Invalid creation parameters

## Files

```text
priority-queue/
+-- priority_queue.h
+-- priority_queue.c
+-- priority_queue_test.c
+-- README.md
```
