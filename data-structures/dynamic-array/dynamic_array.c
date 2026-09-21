#include "dynamic_array.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define MIN_CAPACITY 8
struct DynamicArray {
    unsigned char *data;
    size_t size;
    size_t capacity;
    size_t element_size;
    dynamic_array_free_fn element_free;
};
static int mul_overflow(size_t a, size_t b)
{
    return b != 0 && a > SIZE_MAX / b;
}
static int valid(const DynamicArray *array)
{
    return array != NULL && array->element_size != 0;
}
static unsigned char *at(DynamicArray *array, size_t index)
{
    return array->data + index * array->element_size;
}
static const unsigned char *at_const(
    const DynamicArray *array,
    size_t index
)
{
    return array->data + index * array->element_size;
}
static int resize(DynamicArray *array, size_t capacity)
{
    if (!valid(array) ||
        capacity == 0 ||
        capacity < array->size ||
        mul_overflow(capacity, array->element_size)) {
        return 0;
    }
    if (capacity == array->capacity) {
        return 1;
    }
    unsigned char *data = realloc(
        array->data,
        capacity * array->element_size
    );
    if (data == NULL) {
        return 0;
    }
    array->data = data;
    array->capacity = capacity;
    return 1;
}
static int grow(DynamicArray *array)
{
    if (array->size < array->capacity) {
        return 1;
    }
    if (array->capacity > SIZE_MAX / 2) {
        return 0;
    }
    size_t new_capacity =
        array->capacity == 0
            ? MIN_CAPACITY
            : array->capacity * 2;
    return resize(array, new_capacity);
}
static void shrink(DynamicArray *array)
{
    if (!valid(array) ||
        array->capacity <= MIN_CAPACITY) {
        return;
    }
    if (array->size > array->capacity / 4) {
        return;
    }
    size_t new_capacity = array->capacity / 2;
    if (new_capacity < MIN_CAPACITY) {
        new_capacity = MIN_CAPACITY;
    }
    if (new_capacity < array->size) {
        new_capacity = array->size;
    }
    (void)resize(array, new_capacity);
}
DynamicArray *dynamic_array_create(
    size_t element_size,
    size_t initial_capacity,
    dynamic_array_free_fn element_free
)
{
    if (element_size == 0) {
        return NULL;
    }
    if (initial_capacity < MIN_CAPACITY) {
        initial_capacity = MIN_CAPACITY;
    }
    if (mul_overflow(initial_capacity, element_size)) {
        return NULL;
    }
    DynamicArray *array = malloc(sizeof(*array));
    if (array == NULL) {
        return NULL;
    }
    array->data = malloc(initial_capacity * element_size);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }
    array->size = 0;
    array->capacity = initial_capacity;
    array->element_size = element_size;
    array->element_free = element_free;
    return array;
}
void dynamic_array_destroy(DynamicArray *array)
{
    if (array == NULL) {
        return;
    }
    if (array->element_free != NULL) {
        for (size_t i = 0; i < array->size; ++i) {
            array->element_free(at(array, i));
        }
    }
    free(array->data);
    free(array);
}
int dynamic_array_push(DynamicArray *array, const void *element)
{
    if (!valid(array) || element == NULL) {
        return 0;
    }
    if (!grow(array)) {
        return 0;
    }
    memcpy(
        at(array, array->size),
        element,
        array->element_size
    );
    array->size++;
    return 1;
}
int dynamic_array_pop(DynamicArray *array, void *out_element)
{
    if (!valid(array) || array->size == 0) {
        return 0;
    }
    size_t index = array->size - 1;
    unsigned char *element = at(array, index);
    if (out_element != NULL) {
        memcpy(
            out_element,
            element,
            array->element_size
        );
    } else if (array->element_free != NULL) {
        array->element_free(element);
    }
    array->size--;
    shrink(array);
    return 1;
}
int dynamic_array_insert(
    DynamicArray *array,
    size_t index,
    const void *element
)
{
    if (!valid(array) ||
        element == NULL ||
        index > array->size) {
        return 0;
    }
    if (!grow(array)) {
        return 0;
    }
    size_t move_count = array->size - index;
    if (move_count > 0) {
        memmove(
            at(array, index + 1),
            at(array, index),
            move_count * array->element_size
        );
    }
    memcpy(
        at(array, index),
        element,
        array->element_size
    );
    array->size++;
    return 1;
}
int dynamic_array_remove(
    DynamicArray *array,
    size_t index,
    void *out_element
)
{
    if (!valid(array) || index >= array->size) {
        return 0;
    }
    unsigned char *element = at(array, index);
    if (out_element != NULL) {
        memcpy(
            out_element,
            element,
            array->element_size
        );
    } else if (array->element_free != NULL) {
        array->element_free(element);
    }
    size_t move_count = array->size - index - 1;
    if (move_count > 0) {
        memmove(
            at(array, index),
            at(array, index + 1),
            move_count * array->element_size
        );
    }
    array->size--;
    shrink(array);
    return 1;
}
void *dynamic_array_get(DynamicArray *array, size_t index)
{
    if (!valid(array) || index >= array->size) {
        return NULL;
    }
    return at(array, index);
}
const void *dynamic_array_get_const(
    const DynamicArray *array,
    size_t index
)
{
    if (!valid(array) || index >= array->size) {
        return NULL;
    }
    return at_const(array, index);
}
size_t dynamic_array_size(const DynamicArray *array)
{
    return valid(array) ? array->size : 0;
}
size_t dynamic_array_capacity(const DynamicArray *array)
{
    return valid(array) ? array->capacity : 0;
}
size_t dynamic_array_element_size(const DynamicArray *array)
{
    return valid(array) ? array->element_size : 0;
}
int dynamic_array_reserve(DynamicArray *array, size_t capacity)
{
    if (!valid(array)) {
        return 0;
    }
    if (capacity <= array->capacity) {
        return 1;
    }
    return resize(array, capacity);
}
int dynamic_array_shrink_to_fit(DynamicArray *array)
{
    if (!valid(array)) {
        return 0;
    }
    size_t target = array->size;
    if (target < MIN_CAPACITY) {
        target = MIN_CAPACITY;
    }
    return resize(array, target);
}
int dynamic_array_clear(DynamicArray *array)
{
    if (!valid(array)) {
        return 0;
    }
    if (array->element_free != NULL) {
        for (size_t i = 0; i < array->size; ++i) {
            array->element_free(at(array, i));
        }
    }
    array->size = 0;
    return 1;
}
