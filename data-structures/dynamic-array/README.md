# Generic Dynamic Array

A generic, type-independent dynamic array implementation written in C11.

## Features

- Generic void pointer element storage
- Automatic capacity growth and shrinking
- Push, pop, insert and remove
- O(1) random access
- Custom element destructor callback
- Reserve and shrink-to-fit support
- Overflow-safe allocation
- Allocation-failure handling
- Clear operation
- C11 compatible

## API

- `dynamic_array_create()` - create an array
- `dynamic_array_push()` - append an element
- `dynamic_array_pop()` - remove the last element
- `dynamic_array_insert()` - insert at an index
- `dynamic_array_remove()` - remove at an index
- `dynamic_array_get()` - access an element
- `dynamic_array_reserve()` - increase capacity
- `dynamic_array_shrink_to_fit()` - reduce unused capacity
- `dynamic_array_clear()` - remove all elements
- `dynamic_array_destroy()` - release all resources

## Growth Strategy

The minimum capacity is 8 elements. When the array becomes full, capacity doubles.

``text
8 -> 16 -> 32 -> 64 -> ...

## Shrinking Strategy

When the size becomes less than or equal to one quarter of the capacity, the implementation attempts to halve the capacity. Capacity never falls below 8.

## Complexity

| Operation | Complexity |
|---|---|
| Get | O(1) |
| Push | Amortized O(1) |
| Pop | Amortized O(1) |
| Insert | O(n) |
| Remove | O(n) |
| Reserve | O(n) when reallocating |
| Shrink to fit | O(n) when reallocating |
| Clear | O(n) |

## Testing

The test suite covers basic operations, large workloads, insertion, removal, reserve, shrinking, destructor callbacks, clearing, and invalid operations.

Build and run:

``bash
gcc -std=c11 -Wall -Wextra -Wpedantic data-structures/dynamic-array/dynamic_array.c data-structures/dynamic-array/dynamic_array_test.c -o dynamic_array_test
./dynamic_array_test
``

Expected output:

``text
All dynamic array tests passed.
``

