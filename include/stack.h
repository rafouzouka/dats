#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdbool.h>

#include "linked_list.h"

typedef struct
{
    dats_linked_list_t ll;
} dats_stack_t;

/**
 * @brief Create and initialize a stack data structure. You must use this function to create a stack. 
 * 
 * @param data_size Number of bytes the data is made of that will be stored. 
 * @return dats_stack_t The direct datastructure that you will pass for others functions.
 */
dats_stack_t dats_stack_new(uint64_t data_size);

/**
 * @brief Add any data in the stack at the first position shifting every already existing data.
 * 
 * @param self Pointer to the existing stack to perform the function.
 * @param data A pointer to the data that will be copied into the stack. It's a const void pointer, there will be no alteration to given the paramater data.
 */
void dats_stack_push(dats_stack_t *self, const void *data);

/**
 * @brief Remove any data in the stack at the first position (or the one that has been added the last).
 *
 * @details The data given back isn't free and will not be automaticly by the stack datastrucutre. You must free the data by calling free() on the pointer returned.
 * 
 * @param self Pointer to the existing stack to perform the function.
 * @return void* Pointer to the data that has been removed from the stack. This data must be free by the user.
 */
void *dats_stack_pop(dats_stack_t *self);

/**
 * @brief Get a pointer to the first data to be removed using pop but without removing it.
 *
 * @details Peeking a data doesn't remove it at all in the stack. You must not altered or trying to free the pointer returned. 
 *
 * @param self Pointer to the existing stack to perform the function.
 * @return const void* Pointer to the data that need to be casted. You must not freeing it.
 */
const void *dats_stack_peek(const dats_stack_t *self);

/**
 * @brief Get back a const void pointer to the data at the given index position in the stack. You must not try to modify this data nor freeing it.
 * 
 * @param self Pointer to the existing stack to perform the function.
 * @param index The position in the stack starting from 0 to get the data from. The first element is considered as index 0.
 * @return const void* A pointer of the data at the given index that need to be casted back to the right data type before use.
 */
const void *dats_stack_get(const dats_stack_t *self, uint64_t index);

/**
 * @brief Check if the given data exist in at least once in the stack.
 * 
 * @param self Pointer to the existing stack to perform the function.
 * @param data The data we are trying to find in the data structure. 
 * @return true The data exist at least once.
 * @return false The data isn't in the given stack.
 */
bool dats_stack_contains(const dats_stack_t *self, const void *data);

/**
 * @brief Get the number of elements in the stack. This function does not change the stack.
 * 
 * @param self Pointer to the existing stack to perform the function.
 * @return uint64_t Number of elements in the stack.
 */
uint64_t dats_stack_length(const dats_stack_t *self);

/**
 * @brief Automaticaly clearing all data and the stack passed as parameter. It can be reuse after this.
 * 
 * @param self The stack that will be clear.
 */
void dats_stack_clear(dats_stack_t *self);

/**
 * @brief Automaticaly freeing all data and the stack passed as parameter.
 * 
 * @param self The stack that will be freed.
 */
void dats_stack_free(dats_stack_t *self);

#endif