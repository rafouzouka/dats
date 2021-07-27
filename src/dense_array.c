#include <dats/dense_array.h>
#include <dats/dynamic_array.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "utils.h"
#include "dense_array.h"
#include "dynamic_array.h"

dats_dense_array_t dats_dense_array_new(uint64_t data_size)
{
    dats_dense_array_t da = {
        .lookup = dats_dynamic_array_new(4, sizeof(dats_dense_array_lookup_cell_t)),
        .data = dats_dynamic_array_new(4, data_size),
        .lookup_length = 0,
        .data_length = 0,
        .data_size = data_size,
    };
    
    return da;
}

static void _append_lookup_empty_cells(dats_dynamic_array_t *lookup, uint64_t number)
{
    for (uint64_t i = 0; i < number; i++)
    {
        dats_dense_array_lookup_cell_t empty_cell = {
            .index = 0,
            .data_index = 0,
            .state = DATS_DENSE_ARRAY_CELL_EMPTY,
        };
        dats_dynamic_array_add(lookup, &empty_cell);
    }
}

void dats_dense_array_insert(dats_dense_array_t *self, uint64_t index, const void *data)
{
    if (index >= self->lookup_length)
    {
        _append_lookup_empty_cells(&self->lookup, (index+1) - self->lookup_length);
        self->lookup_length = index + 1;
    }
    
    dats_dense_array_lookup_cell_t *current_cell = dats_dynamic_array_ref(&self->lookup, index); 
    if (current_cell->state == DATS_DENSE_ARRAY_CELL_EMPTY)
    {
        current_cell->index = self->data_length;
        current_cell->state = DATS_DENSE_ARRAY_CELL_DATA;
        dats_dense_array_lookup_cell_t *corresponding_cell = dats_dynamic_array_ref(&self->lookup, self->data_length);
        corresponding_cell->data_index = index;
        dats_dynamic_array_add(&self->data, data);
        self->data_length++;
    }
    else
    {
        dats_dynamic_array_insert(&self->data, current_cell->index, data);
    }
}

void dats_dense_array_remove(dats_dense_array_t *self, uint64_t index)
{
    assert(index < self->lookup_length);

    dats_dense_array_lookup_cell_t *lookup_cell = dats_dynamic_array_ref(&self->lookup, index);
    if (lookup_cell->state == DATS_DENSE_ARRAY_CELL_EMPTY)
    {
        DATS_RAISE_ERROR("Trying to remove an empty cell.");
        return;
    }

    self->data_length--;
    lookup_cell->state = DATS_DENSE_ARRAY_CELL_EMPTY;
    
    void *data_to_swap = dats_dynamic_array_ref(&self->data, self->data_length);
    dats_dynamic_array_insert(&self->data, lookup_cell->index, data_to_swap);

    dats_dense_array_lookup_cell_t *corresponding_data_cell = dats_dynamic_array_ref(&self->lookup, self->data_length);
    dats_dense_array_lookup_cell_t *cell_to_redirect = dats_dynamic_array_ref(&self->lookup, corresponding_data_cell->data_index);
    cell_to_redirect->index = lookup_cell->index;

    dats_dense_array_lookup_cell_t *cell_to_data_redirect = dats_dynamic_array_ref(&self->lookup, lookup_cell->index);
    cell_to_data_redirect->data_index = corresponding_data_cell->data_index;
}

const void *dats_dense_array_get(const dats_dense_array_t *self, uint64_t index)
{
    assert(index < self->lookup_length);

    const dats_dense_array_lookup_cell_t *cell = dats_dynamic_array_get(&self->lookup, index);
    if (cell->state == DATS_DENSE_ARRAY_CELL_EMPTY)
    {
        DATS_RAISE_ERROR("There is no data associated to that cell.");
    }
    return dats_dynamic_array_get(&self->data, cell->index);
}

void *dats_dense_array_ref(dats_dense_array_t *self, uint64_t index)
{
    assert(index < self->lookup_length);

    dats_dense_array_lookup_cell_t *cell = dats_dynamic_array_ref(&self->lookup, index);
    if (cell->state == DATS_DENSE_ARRAY_CELL_EMPTY)
    {
        DATS_RAISE_ERROR("There is no data associated to that cell.");
    }
    return dats_dynamic_array_ref(&self->data, cell->index);
}

bool dats_dense_array_contains(const dats_dense_array_t *self, const void *data)
{
    for (uint64_t i = 0; i < self->data_length; i++)
    {
        if (memcmp(dats_dynamic_array_get(&self->data, i), data, self->data_size) == 0)
        {
            return true;
        }
    }
    return false;
}

void dats_dense_array_clear(dats_dense_array_t *self)
{
    dats_dynamic_array_clear(&self->lookup);
    dats_dynamic_array_clear(&self->data);
    self->data_length = 0;
    self->lookup_length = 0;
}

void dats_dense_array_print(const dats_dense_array_t *self)
{
    printf("LOOKUP l: %ld:\n", self->lookup_length);
    for (uint64_t i = 0; i < self->lookup_length; i++)
    {
        const dats_dense_array_lookup_cell_t *cell = dats_dynamic_array_get(&self->lookup, i);
        if (cell->state == DATS_DENSE_ARRAY_CELL_EMPTY)
        {
            printf("[X] ");
        }
        else
        {
            printf("[%ld] ", cell->index);
        }
    }
    printf("\n");

    printf("DATA l: %ld:\n", self->data_length);
    for (uint64_t i = 0; i < self->data_length; i++)
    {
        const double *data = dats_dynamic_array_get(&self->data, i);
        printf("[%f] ", *data);
    }
    printf("\n\n");
}

void dats_dense_array_free(dats_dense_array_t *self)
{
    dats_dynamic_array_free(&self->lookup);
    dats_dynamic_array_free(&self->data);
    self->data_size = 0;
    self->data_length = 0;
    self->lookup_length = 0;
}
