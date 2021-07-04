#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

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

/**
 * @brief Insert data in the index position replacing data previously in there. This method does not change the length or the capacity.
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param index Position you want to insert th data. 
 * @param data Data we want to insert in the Dynamic Array.
 */
void dats_dynamic_array_insert(dats_dynamic_array_t *self, uint64_t index, const void *data);

/**
 * @brief Create a new slot at the end of the dynamic array and insert the given data in it.
 * 
 * @details If the capacity isn't enought in the dynamic array internally for adding the data a new bigger will be created and populated with the previous data. 
 *
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param data Data we want to insert in the Dynamic Array.
 */
void dats_dynamic_array_add(dats_dynamic_array_t *self, const void *data);

/**
 * @brief Remove the first occurence of the specified data. This will shift every next item following the data to the left. 
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param data Data we want to remove in the Dynamic Array.
 */
void dats_dynamic_array_remove(dats_dynamic_array_t *self, const void *data);

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

/**
 * @brief Check if the given data exist in at least once in the dynamic array.
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 * @param data The data we are trying to find in the data structure. 
 * @return true The data exist at least once.
 * @return false The data isn't in the given dynamic array.
 */
bool dats_dynamic_array_contains(const dats_dynamic_array_t *self, const void *data);

/**
 * @brief Find the index position of the first matching data in the dynamic array. It starts at position 0.
 *
 * @details If you provide an empty dynamic list the function will assert. Else if the data don't match with anything the program exits and writes the error to stderr.  
 *
 * @param self Pointer to the existing dynamic list to perform the function.
 * @param data The data that must match with at least one data in the dynamic list. We are not comparing the pointers but the real memory that is pointed.
 * @return uint64_t Index position, starting by 0, of the first match with the data provided in the params.
 */
uint64_t dats_dynamic_array_find_index(const dats_dynamic_array_t *self, const void *data);

/**
 * @brief Get the number of elements in the dynamic array. This function does not change the dynamic array.
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 * @return uint64_t Number of elements in the dynamic array.
 */
uint64_t dats_dynamic_array_length(const dats_dynamic_array_t *self);

/**
 * @brief Emptying all data in the dynamic array but still keeping original capacity. This is clearing the data inside the dynamic array but this is not the way to free it.
 * 
 * @param self Pointer to the existing dynamic array to perform the function.
 */
void dats_dynamic_array_clear(dats_dynamic_array_t *self);

/**
 * @brief Free all the memory used by the data structure.
 * 
 * @param self The dynamic array that will be freed.
 */
void dats_dynamic_array_free(dats_dynamic_array_t *self);

#endif