#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>

typedef enum
{
    DATS_BITSET_LOW = 0,
    DATS_BITSET_HIGH = 1,
} dats_bitset_state;

typedef struct
{
    void *buffer;
    uint64_t size;
    uint64_t bytes_needed;
} dats_bitset_t;

dats_bitset_t dats_bitset_new(uint64_t size);

void dats_bitset_set(dats_bitset_t *self, uint64_t position, dats_bitset_state state);

// flip

void dats_bitset_reset(dats_bitset_t *self);

// changer le print en to_string
void dats_bitset_print(const dats_bitset_t *self);

void dats_bitset_free(dats_bitset_t *self);

#endif