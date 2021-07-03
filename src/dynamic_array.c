#include <stdlib.h>

#include "dynamic_array.h"

dats_dynamic_array_t dats_dynamic_array_new(uint64_t capacity, uint64_t data_size)
{
    dats_dynamic_array_t da = {
        .data_size = data_size,
        .length = 0,
        .capacity = capacity,
        .buffer = calloc(capacity, data_size)
    };
    return da;
}

void dats_dynamic_array_free(dats_dynamic_array_t *self)
{
    self->capacity = 0;
    self->length = 0;
    
    free(self->buffer);
    self->buffer = NULL;
}
