#ifndef _DARRAY_H_
#define _DARRAY_H_

typedef struct DArray {
    int size;
    int capacity;
    void **elements;
} DArray;

DArray *
DArray_create(int capacity);

void *
DArray_get(DArray *array, int index);

void *
DArray_set(DArray *array, void *element, int index);

void
DArray_destroy(DArray *array);

#endif
