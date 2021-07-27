#ifndef DENSE_ARRAY_H
#define DENSE_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

#include "dynamic_array.h"

typedef enum
{
    DATS_DENSE_ARRAY_CELL_EMPTY,
    DATS_DENSE_ARRAY_CELL_DATA,
} dats_dense_array_lookup_state_t;

typedef struct
{
    dats_dense_array_lookup_state_t state;
    uint64_t index;
    uint64_t data_index;
} dats_dense_array_lookup_cell_t;

typedef struct
{
    dats_dynamic_array_t lookup;
    dats_dynamic_array_t data;
    uint64_t data_length;
    uint64_t lookup_length;
    uint64_t data_size;
} dats_dense_array_t;

dats_dense_array_t dats_dense_array_new(uint64_t data_size);

void dats_dense_array_insert(dats_dense_array_t *self, uint64_t index, const void *data);

void dats_dense_array_remove(dats_dense_array_t *self, uint64_t index);

const void *dats_dense_array_get(const dats_dense_array_t *self, uint64_t index);

void *dats_dense_array_ref(dats_dense_array_t *self, uint64_t index);

bool dats_dense_array_contains(const dats_dense_array_t *self, const void *data);

void dats_dense_array_clear(dats_dense_array_t *self);

void dats_dense_array_print(const dats_dense_array_t *self);

void dats_dense_array_free(dats_dense_array_t *self);

#endif