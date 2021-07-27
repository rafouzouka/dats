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

/**
 * @brief Create a Dense Array that hold generic data type. A Dense array is composed by two dynamic array. One that hold the data and the other a lookup table.
 * 
 * @param data_size The number of bytes needed for the data type you want to use with the dense array.
 * @return dats_dense_array_t The data structure that you will pass through functions. You must not change the values of the struct.
 */
dats_dense_array_t dats_dense_array_new(uint64_t data_size);

/**
 * @brief Insert data in the index position replacing data previously in there if any.
 * 
 * @details Only the lookup table will be sparse the dynamic table will automaticly be contiguous. 
 *
 * @param self Pointer to the existing dense array to perform the function.
 * @param index Position you want to insert the data. 
 * @param data Data we want to insert in the Dense Array.
 */
void dats_dense_array_insert(dats_dense_array_t *self, uint64_t index, const void *data);

/**
 * @brief Remove the data at the specified index. 
 * 
 * @param self Pointer to the existing dense array to perform the function.
 * @param index Position you want to remove the data. 
 */
void dats_dense_array_remove(dats_dense_array_t *self, uint64_t index);

/**
 * @brief Get a const pointer to the data at a given index in the Dense Array. You must not try to free or modify the value.
 * 
 * @param self Pointer to the existing dense array to perform the function.
 * @param index Position you want to get the data in the dense array. 
 * @return const void* Direct access to the wanted data in the memory. Don't modify it.
 */
const void *dats_dense_array_get(const dats_dense_array_t *self, uint64_t index);

/**
 * @brief Get a pointer to the data at a given index in the Dense Array. You must not try to free the value.
 * 
 * @param self Pointer to the existing dense array to perform the function.
 * @param index Position you want to get the data in the dense array. 
 * @return void* Direct access to the wanted data in the memory. Don't free it.
 */
void *dats_dense_array_ref(dats_dense_array_t *self, uint64_t index);

/**
 * @brief Check if the given data exist in at least once in the dense array.
 * 
 * @param self Pointer to the existing dense array to perform the function.
 * @param data The data we are trying to find in the data structure. 
 * @return true The data exist at least once.
 * @return false The data isn't in the given dense array.
 */
bool dats_dense_array_contains(const dats_dense_array_t *self, const void *data);

/**
 * @brief Emptying all data in the dense array but still keeping original capacity. This is clearing the data inside the dense array but this is not the way to free it.
 * 
 * @param self Pointer to the existing dense array to perform the function.
 */
void dats_dense_array_clear(dats_dense_array_t *self);

void dats_dense_array_print(const dats_dense_array_t *self);

/**
 * @brief Free all the memory used by the data structure.
 * 
 * @param self The dense array that will be freed.
 */
void dats_dense_array_free(dats_dense_array_t *self);

#endif