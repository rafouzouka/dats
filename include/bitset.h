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

/**
 * @brief Set the state of a precise bit in the bitset as true for 1 or false for 0. By default all the bit are set to false.
 * 
 * @param self Pointer to the existing bitset to perform the function.
 * @param position Place in the bitset of the bit that will be set. Starting from 1.
 * @param state true to set to 1 and false to set to 0 the bit.
 */
void dats_bitset_set(dats_bitset_t *self, uint64_t position, bool state);

/**
 * @brief Inverse all the bit state in the bitset.
 * 
 * @param self Pointer to the existing bitset to perform the function.
 */
void dats_bitset_flip(dats_bitset_t *self);

/**
 * @brief Test if a bit is set or not at a given position.
 * 
 * @param self Pointer to the existing bitset to perform the function.
 * @param position Place in the bitset of the bit that will be tested. Starting from 1.
 * @return true Bit is set.
 * @return false Bit isn't set.
 */
bool dats_bitset_is_set(const dats_bitset_t *self, uint64_t position);

/**
 * @brief Test if a all the bits in the other bitset are also set in the self bitset.
 * 
 * @param self Pointer to the existing bitset to perform the function.
 * @param other Other already initializes bitset that must be the same size.
 * @return true Bits are set.
 * @return false Bits are set.
 */
bool dats_bitset_is_set_bitset(const dats_bitset_t *self, const dats_bitset_t *other);

/**
 * @brief Set to 0 all the bit in the bitset and can still be use after this.
 * 
 * @param self Pointer to the existing bitset to perform the function.
 */
void dats_bitset_reset(dats_bitset_t *self);

void dats_bitset_print(const dats_bitset_t *self);

/**
 * @brief Free the bitset completly and can't be used after this. If you just want to clear the bitset use reset instead.
 * 
 * @param self The bitset that will be freed.
 */
void dats_bitset_free(dats_bitset_t *self);

#endif