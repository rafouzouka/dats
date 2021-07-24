#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bitset.h"
#include "utils.h"

dats_bitset_t dats_bitset_new(uint64_t size)
{
    assert(size > 0);

    uint64_t bytes_needed = size / 8;
    if (size % 8 != 0)
    {
        bytes_needed++;
    }

    dats_bitset_t bt = {
        .buffer = DATS_OOM_GUARD(calloc(bytes_needed, 1)),
        .size = size,
        .bytes_needed = bytes_needed
    };

    return bt;
}

void dats_bitset_set(dats_bitset_t *self, uint64_t position, bool state)
{
    assert(position > 0);
    assert(position <= self->size);

    position--;

    uint8_t *bytes = self->buffer;

    uint64_t complete_bytes = position / 8;
    uint64_t leftovers = position % 8;

    uint8_t mask = 0b10000000;

    if (leftovers > 0)
    {
        mask = mask >> leftovers;
    }

    if (state == true)
    {
        bytes[complete_bytes] |= mask; 
    }
    else
    {
        mask = ~mask;
        bytes[complete_bytes] &= mask;
    }
}

void dats_bitset_flip(dats_bitset_t * self)
{
    uint8_t *bytes = self->buffer;

    for (uint64_t i = 0; i < self->bytes_needed; i++)
    {
        bytes[i] = ~bytes[i];
    }
}

bool dats_bitset_is_set(const dats_bitset_t *self, uint64_t position)
{
    assert(position > 0);
    assert(position <= self->size);
    
    position--;

    uint64_t complete_bytes = position / 8;
    uint64_t leftovers = position % 8;

    uint8_t mask = 0b10000000 >> leftovers;
    uint8_t *bytes = self->buffer; 

    if ((bytes[complete_bytes] & mask) == 0)
    {
        return false;
    }
    return true;
}

void dats_bitset_reset(dats_bitset_t *self)
{
    memset(self->buffer, 0, self->bytes_needed);
}

static void _print_byte(uint8_t byte, uint64_t number)
{
    assert(number <= 8);

    for (uint64_t i = 0; i < number; i++)
    {
        printf("%c", (byte & 0b10000000) ? '1' : '0');
        byte = byte << 1;
    }
}

void dats_bitset_print(const dats_bitset_t *self)
{
    uint8_t *bytes = self->buffer;

    uint64_t complete_bytes = self->size / 8;
    uint64_t leftovers = self->size % 8;

    for (uint64_t i = 0; i < complete_bytes; i++)
    {
        _print_byte(bytes[i], 8);
        printf(" ");
    }
    _print_byte(bytes[complete_bytes], leftovers);

    printf("\n");
}

void dats_bitset_free(dats_bitset_t *self)
{
    free(self->buffer);
    self->buffer = NULL;
    self->bytes_needed = 0;
    self->size = 0;
}
