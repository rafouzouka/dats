#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

dats_linked_list_t dats_linked_list_new(const uint64_t data_size)
{
    assert(data_size > 0);

    dats_linked_list_t ll = {
        .head = NULL,
        .tail = NULL,
        .data_size = data_size,
        .length = 0
    };
    return ll;
}

const void *dats_linked_list_get_data(const dats_linked_list_t *self, const uint64_t index)
{
    assert(index < self->length);

    dats_node_t *current_node = self->head; 

    for (uint64_t i = 0; i < index; i++)
    {
        current_node = current_node->next_node;
    }

    return current_node->data;
}

void dats_linked_list_insert_head(dats_linked_list_t *self, const void *data)
{
    dats_node_t *node = malloc(sizeof(dats_node_t));
    node->data = malloc(sizeof(self->data_size));

    memcpy(node->data, data, self->data_size);

    node->next_node = self->head;
    self->head = node;
    self->length++;

    if (self->tail == NULL)
    {
        self->tail = self->head;
    }
}

void dats_linked_list_free(dats_linked_list_t *self)
{
    dats_node_t *current_node = self->head;

    while (current_node != NULL)
    {
        dats_node_t *next_node = current_node->next_node;

        free(current_node->data);
        current_node->data = NULL;
        free(current_node);

        current_node = next_node;
    }

    self->head = NULL;
    self->tail = NULL;
    self->length = 0;
}
