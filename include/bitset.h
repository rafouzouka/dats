#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    void *buffer;
    uint64_t size;
    uint64_t bytes_needed;
} dats_bitset_t;

/**
 * @brief Create and initialize a bitset. You must use this function to create a bitset. 
 * 
 * @param size Total length of the bitset. All the bit is initialized with 0 or false.
 * @return dats_bitset_t The direct datastructure that you will pass for others functions.
 */
dats_bitset_t dats_bitset_new(uint64_t size);

void dats_bitset_set(dats_bitset_t *self, uint64_t position, bool state);

void dats_bitset_flip(dats_bitset_t *self);

bool dats_bitset_is_set(const dats_bitset_t *self, uint64_t position);

void dats_bitset_reset(dats_bitset_t *self);

void dats_bitset_print(const dats_bitset_t *self);

/**
 * @brief Free the bitset completly and can't be used after this. If you just want to clear the bitset use reset instead.
 * 
 * @param self The bitset that will be freed.
 */
void dats_bitset_free(dats_bitset_t *self);

#endif