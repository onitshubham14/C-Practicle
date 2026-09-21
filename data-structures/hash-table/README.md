# Generic Hash Table in C

A reusable generic hash table implementation in C using separate chaining for collision resolution.

## Features

- Generic void* keys and values
- User-defined hash and equality callbacks
- Separate chaining for collisions
- Automatic growth above 0.75 load factor
- Automatic shrinking below 0.20 load factor
- Explicit reserve and rehash support
- Duplicate-key update support
- Optional key/value ownership callbacks
- Collision statistics
- Allocation-failure handling
- C11-compatible implementation

## Files

| File | Description |
|---|---|
| hash_table.h | Public API |
| hash_table.c | Hash table implementation |
| hash_table_test.c | Automated test suite |

## Compile

gcc -std=c11 -Wall -Wextra -Wpedantic hash_table.c hash_table_test.c -o hash_table_test

## Run

./hash_table_test

## Complexity

With a well-distributed hash function, insert, lookup and removal are expected to run in average O(1) time.

| Operation | Average | Worst |
|---|---:|---:|
| Insert | O(1) | O(n) |
| Lookup | O(1) | O(n) |
| Remove | O(1) | O(n) |
| Resize | O(n) | O(n) |

The worst case occurs when multiple keys map to the same bucket.

## Ownership

The table does not copy keys or values.

Optional free callbacks can be supplied when creating the table. When provided, these callbacks release key and value memory when entries are replaced, removed, or the table is destroyed.

## Testing

The test suite covers:

- Basic insertion and lookup
- Missing keys
- Duplicate-key updates
- Deterministic collision chains
- Automatic growth
- Explicit reserve and rehashing
- Automatic shrinking
- Large workloads
- Null and invalid input handling
