#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*dynamic_array_free_fn)(void *element);

typedef struct DynamicArray DynamicArray;

DynamicArray *dynamic_array_create(
    size_t element_size,
    size_t initial_capacity,
    dynamic_array_free_fn element_free
);

void dynamic_array_destroy(DynamicArray *array);

int dynamic_array_push(DynamicArray *array, const void *element);
int dynamic_array_pop(DynamicArray *array, void *out_element);

int dynamic_array_insert(
    DynamicArray *array,
    size_t index,
    const void *element
);

int dynamic_array_remove(
    DynamicArray *array,
    size_t index,
    void *out_element
);

void *dynamic_array_get(DynamicArray *array, size_t index);
const void *dynamic_array_get_const(const DynamicArray *array, size_t index);

size_t dynamic_array_size(const DynamicArray *array);
size_t dynamic_array_capacity(const DynamicArray *array);
size_t dynamic_array_element_size(const DynamicArray *array);

int dynamic_array_reserve(DynamicArray *array, size_t capacity);
int dynamic_array_shrink_to_fit(DynamicArray *array);

int dynamic_array_clear(DynamicArray *array);

#ifdef __cplusplus
}
#endif

#endif
