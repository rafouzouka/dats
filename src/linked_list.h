#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

typedef struct _dats_node_t dats_node_t;

/**
 * @brief The node structure should not only use internally.
 * 
 * The next_node point the next following
 * node or NULL if there isn't. Making the data a void pointer allow
 * us to make it "generic".  
 */
typedef struct _dats_node_t
{
    dats_node_t *next_node;
    void *data;
} dats_node_t;

typedef struct _dats_linked_list_t
{
    dats_node_t *head;
    dats_node_t *tail;
    const uint64_t data_size;
    uint64_t length;
} dats_linked_list_t;

/**
 * @brief Creating and initialize new linked_list ready to use.
 * 
 * @param data_size Number of bytes of the data that will be stored. 
 * @return dats_linked_list_t The resulting linked list created. 
 */
dats_linked_list_t dats_linked_list_new(const uint64_t data_size);

/**
 * @brief Getting a const pointer to the data associated to the node described by his index.
 * 
 * @param self Pointer to the existing linked list to perform the function.
 * @param index The index corresponding to the node position in the linked list, starting from 0.
 * @return const void* Pointer to the heap alocated data. Must not be changed or freed.
 */
const void *dats_linked_list_get_data(const dats_linked_list_t *self, const uint64_t index);

/**
 * @brief Add a new node heap allocated with data at the first position of the linked list.
 * 
 * @details If you append to an empty linked list the head and the tail will point to the same new node.
 * 
 * @param self Pointer to the linked list waiting for the new node.
 * @param data Void pointer to the data that will copy to the new node data. You must provide data with the same type that you use for the creation of the linked list.
 */
void dats_linked_list_insert_head(dats_linked_list_t *self, const void *data);


/**
 * @brief Add a new node heap allocated with data at the last position of the LinkedList.
 *
 * @details If you append to an empty linked list the head and the tail will point to the same new node.
 *
 * @param self Pointer to the linked list waiting for the new node.
 * @param data Void pointer to the data that will copy to the new node data. You must provide data with the same type that you use for the creation of the linked list.
 */
void dats_linked_list_insert_tail(dats_linked_list_t *self, const void *data);

/**
 * @brief Free an already existing linked_list. Freeing the every nodes and each correspondig data.
 * 
 * @param self Pointer to existing Linked List already created with the dats_linked_list_new function.
 */
void dats_linked_list_free(dats_linked_list_t *self);

#endif