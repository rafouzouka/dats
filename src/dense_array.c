#include <stdint.h>
#include <stdlib.h>

#include "dense_array.h"
#include "dynamic_array.h"

typedef enum
{
    DATS_DENSE_ARRAY_CELL_EMPTY,
    DATS_DENSE_ARRAY_CELL_DATA,
} dats_dense_array_state;

typedef struct
{
    dats_dense_array_state state;
    uint64_t index;
} dats_dense_array_cell;

dats_dense_array_t dats_dense_array_new(uint64_t data_size)
{
    const uint64_t initial_capacity = 4;
    dats_dense_array_t da = {
        .lookup = dats_dynamic_array_new(initial_capacity, sizeof(dats_dense_array_cell)),
        .data = dats_dynamic_array_new(initial_capacity, data_size),
        .data_size = data_size,
        .data_length = 0
    };

    // dats_dense_array_cell empty = {
    //     .index = 0,
    //     .state = DATS_DENSE_ARRAY_CELL_EMPTY
    // };

    // for (uint64_t i = 0; i < initial_capacity; i++)
    // {
    //     // dats_dynamic_array_add(dats_dynamic_array_t *self, const void *data)
    // }    

    return da;
}

// voir ce qu'il se passe quand on insert dans une mauvaise
// zone
// void dats_dense_array_insert(dats_dense_array_t *self, uint64_t index, const void* data)
// {
//     dats_dense_array_cell empty = {
//         .index = self->data_length,
//         .state = DATS_DENSE_ARRAY_CELL_DATA
//     };

//     dats_dynamic_array_insert(&self->lookup, index, &self->data_length);
//     dats_dynamic_array_insert(&self->data, self->data_length, data);
// }

void dats_dense_array_free(dats_dense_array_t *self)
{
    dats_dynamic_array_free(&self->lookup);
    dats_dynamic_array_free(&self->data);
}