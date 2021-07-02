#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>

typedef struct _dats_node_t dats_node_t;

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

void dats_linked_list_free(dats_linked_list_t *self);

#endif