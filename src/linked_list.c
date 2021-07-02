#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

static dats_node_t *_alloc_node(const uint64_t data_size);

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

const void *dats_linked_list_get(const dats_linked_list_t *self, const uint64_t index)
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
    dats_node_t *node = _alloc_node(self->data_size);
    memcpy(node->data, data, self->data_size);

    node->next_node = self->head;
    self->head = node;
    self->length++;

    if (self->tail == NULL)
    {
        self->tail = self->head;
    }
}

void dats_linked_list_insert_tail(dats_linked_list_t *self, const void *data)
{
    dats_node_t *new_node = _alloc_node(self->data_size);
    memcpy(new_node->data, data, self->data_size);
    self->length++;

    if (self->head == NULL)
    {
        self->head = new_node;
        self->tail = new_node;
        return;
    }

    self->tail->next_node = new_node;
    self->tail = new_node;
}

void dats_linked_list_map(const dats_linked_list_t *self, void (*func)(const void *data))
{
    dats_node_t *current_node = self->head;

    while (current_node != NULL)
    {
        dats_node_t *next_node = current_node->next_node;

        func(current_node->data);        

        current_node = next_node;
    }
}

// voir si y'a pas moyen de quitter de façon plus stylé
// avec genre un enum 
uint64_t dats_linked_list_find(const dats_linked_list_t *self, const void *data)
{
    assert(self->length > 0);

    dats_node_t *current_node = self->head;
    uint64_t index = 0;

    while (current_node != NULL)
    {
        dats_node_t *next_node = current_node->next_node;

        if (memcmp(current_node->data, data, self->data_size) == 0)
        {
            return index;
        }

        current_node = next_node;
        index++;
    }

    fprintf(stderr, "[ERROR]: Unable to find the data in file: %s at line: %d.\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
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

static dats_node_t *_alloc_node(const uint64_t data_size)
{
    dats_node_t *node = malloc(sizeof(dats_node_t));
    node->data = malloc(data_size);
    node->next_node = NULL;
    return node;
}
