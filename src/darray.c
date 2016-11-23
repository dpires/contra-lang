#include "darray.h"
#include <stdlib.h>

void *
DArray_get(DArray *array, int index)
{
    if (index < 0 || index >= array->capacity)
        return NULL;

    return array->elements[index];
}

void *
DArray_set(DArray *array, void *element, int index)
{
    if (index < 0 || index >= array->capacity)
        return NULL;

    void *tmp = array->elements[index];
    array->elements[index] = element;
    return tmp;
}

DArray *
DArray_create(int capacity)
{
    DArray *array = malloc(sizeof(DArray));
    array->capacity = capacity;
    array->elements = calloc(array->capacity, array->capacity * sizeof(void *));
    array->size = capacity;
    return array;
}

void
DArray_destroy(DArray *array)
{
    free(array->elements);
    free(array);
}
