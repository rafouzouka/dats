#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

#include "linked_list.h"

/**
 * @brief This abstract data structure is implemented using a Linked List.
 * Allowing O(1) enqueue and dequeue. The Queue data strucuture is implemented as FIFO.
 */
typedef struct
{
    dats_linked_list_t ll;
} dats_queue_t;

/**
 * @brief Create and initialize a queue data structure. You must use this function to create a queue. 
 * 
 * @param data_size Number of bytes the data is made of that will be stored. 
 * @return dats_queue_t The direct datastructure that you will pass for others functions.
 */
dats_queue_t dats_queue_new(uint64_t data_size);

/**
 * @brief Add any data in the queue at the last position.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @param data A pointer to the data that will be copied into the queue. It's a const void pointer, there will be no alteration to given the paramater data.
 */
void dats_queue_enqueue(dats_queue_t *self, const void *data);

/**
 * @brief Remove any data in the queue at the last position (or the one that has been added the fisrt).
 *
 * @details The data given back isn't free and will not be automaticly by the Queue datastrucutre. You must free the data by calling free() on the pointer returned.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @return void* Pointer to the data that has been removed from the queue. This data must be free by the user.
 */
void *dats_queue_dequeue(dats_queue_t *self);

/**
 * @brief Get a pointer to the first data to be removed using dequeue but without removing it.
 *
 * @details Peeking a data doesn't remove it at all in the queue. You must not altered or trying to free the pointer returned. 
 *
 * @param self Pointer to the existing queue to perform the function.
 * @return const void* Pointer to the data that need to be casted. You must not freeing it.
 */
const void *dats_queue_peek(const dats_queue_t *self);

/**
 * @brief Get back a const void pointer to the data at the given index position in the queue. You must not try to modify this data nor freeing it.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @param index The position in the queue starting from 0 to get the data from. The first element is considered as index 0.
 * @return const void* A pointer of the data at the given index that need to be casted back to the right data type before use.
 */
const void *dats_queue_get(const dats_queue_t *self, uint64_t index);

/**
 * @brief Invoke the function passed as paramater for each item in the queue. It's start from the last item added and go throught the first item previously added. You must not try to modify or free the data passed to the function.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @param func A function pointer to a real function that the user can provide. It must respect the definition of the function.
 */
void dats_queue_map(const dats_queue_t *self, void (*func)(const void*data));

/**
 * @brief Check if the given data exist in at least once in the queue.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @param data The data we are trying to find in the data structure. 
 * @return true The data exist at least once.
 * @return false The data isn't in the given queue.
 */
bool dats_queue_contains(const dats_queue_t *self, const void *data);

/**
 * @brief Get the number of elements in the queue. This function does not change the queue.
 * 
 * @param self Pointer to the existing queue to perform the function.
 * @return uint64_t Number of elements in the queue.
 */
uint64_t dats_queue_length(const dats_queue_t *self);

/**
 * @brief Automaticaly clearing all data and the queue passed as parameter. It can be reuse after this.
 * 
 * @param self The queue that will be clear.
 */
void dats_queue_clear(dats_queue_t *self);

/**
 * @brief Automaticaly freeing all data and the queue passed as parameter.
 * 
 * @param self The queue that will be freed.
 */
void dats_queue_free(dats_queue_t *self);

#endif