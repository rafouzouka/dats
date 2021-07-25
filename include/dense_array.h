#ifndef DENSE_ARRAY_H
#define DENSE_ARRAY_H

#include <stdint.h>

#include "dynamic_array.h"

typedef struct
{
    dats_dynamic_array_t lookup;
    dats_dynamic_array_t data;
    const uint64_t data_size;
    uint64_t data_length;
} dats_dense_array_t;

// dats_dense_array_t dats_dense_array_new(uint64_t data_size);

// insert
// void dats_dense_array_insert(dats_dense_array_t *self, uint64_t index, const void* data);

// retrieve

// remove

// get

// contains / find / clear / slice

// void dats_dense_array_free(dats_dense_array_t *self);

#endif