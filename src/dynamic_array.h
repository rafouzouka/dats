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

/**
 * @brief Create a Dynamic Array that hold generic data type with an intial capacity.
 * 
 * @details It's required to call the dats_dynamic_array_free to free the memory used by the Dynamic Array. You must not do it yourself.
 *
 * @param capacity Initial length of the array. The Dynamic Array will grow only if you insert a element higher than the given capacity.
 * @param data_size The number of bytes needed for the data type you want to use with the dynamic array.  
 * @return dats_dynamic_array_t The data structure that you will pass through functions. You must not change the values of the struct.
 */
dats_dynamic_array_t dats_dynamic_array_new(uint64_t capacity, uint64_t data_size);

// insert

/**
 * @brief Create a new slot at the end of the dynamic array and insert the given data in it.
 * 
 * @details If the capacity isn't enought in the dynamic array internally for adding the data a new bigger will be created and populated with the previous data. 
 *
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param data Data we want to insert in the Dynamic Array.
 */
void dats_dynamic_array_add(dats_dynamic_array_t *self, const void *data);

// remove

/**
 * @brief Invoke the function passed as paramater for each slots in the dynamic array.
 * 
 * @details You must not try to modify or free the data passed to the function.
 *
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param func A function pointer to a real function that the user can provide. It must respect the definition of the function.
 */
void dats_dynamic_array_map(const dats_dynamic_array_t *self, void (*func)(const void*));

/**
 * @brief Get a const pointer to the data at a given index in the Dynamic Array. You must not try to free or modify the value.
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param index The position of the data in the Dynamic Array you want to get back a pointer from.  
 * @return const void* Direct access to the wanted data in the memory. Don't modify it.
 */
const void* dats_dynamic_array_get(const dats_dynamic_array_t *self, uint64_t index);

// contains

// find

// length

// clear

// reverse

/**
 * @brief Free all the memory used by the data structure.
 * 
 * @param self The dynamic array that will be freed.
 */
void dats_dynamic_array_free(dats_dynamic_array_t *self);

#endif