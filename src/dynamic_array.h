#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdint.h>

typedef struct
{
    const uint64_t data_size;
    uint64_t capacity;
    uint64_t length;
    void *buffer;
} dats_dynamic_array_t;

dats_dynamic_array_t dats_dynamic_array_new(uint64_t capacity, uint64_t data_size);

void dats_dynamic_array_free(dats_dynamic_array_t *self);

#endif