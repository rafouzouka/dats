#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

static dats_node_t *_alloc_node(uint64_t data_size);
static void *_free_node(dats_node_t *node_to_free);
static dats_node_t *_get_node(dats_node_t *start, uint64_t index);

dats_linked_list_t dats_linked_list_new(uint64_t data_size)
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

const void *dats_linked_list_get(const dats_linked_list_t *self, uint64_t index)
{
    assert(index < self->length);

    dats_node_t *node = _get_node(self->head, index);

    return node->data;
}

const void *dats_linked_list_get_head(const dats_linked_list_t *self)
{
    assert(self->length > 0);

    return self->head->data;
}

const void *dats_linked_list_get_tail(const dats_linked_list_t *self)
{
    assert(self->length > 0);

    return self->tail->data;
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

void dats_linked_list_insert_index(dats_linked_list_t *self, uint64_t index, const void *data)
{
    assert(index <= self->length);

    if (index == 0)
    {
        dats_linked_list_insert_head(self, data);
    }
    else if (index == self->length)
    {
        dats_linked_list_insert_tail(self, data);
    }
    else
    {
        dats_node_t *previous_node_from_index = _get_node(self->head, index-1);
        dats_node_t *following_node_from_index = previous_node_from_index->next_node;
        
        dats_node_t *new_node = _alloc_node(self->data_size);
        previous_node_from_index->next_node = new_node;
        new_node->next_node = following_node_from_index;
        self->length++;
    }
}

void *dats_linked_list_remove_head(dats_linked_list_t *self)
{
    assert(self->length > 0);

    dats_node_t *next_node = self->head->next_node;

    void *data = _free_node(self->head);

    if (self->length == 1)
    {
        self->tail = NULL;
    }

    self->head = next_node;
    self->length--;
    return data;
}

void *dats_linked_list_remove_tail(dats_linked_list_t *self)
{
    assert(self->length > 0);

    if (self->length == 1)
    {
        void *data = _free_node(self->tail);
        self->tail = NULL;
        self->head = NULL;
        self->length--;
        return data;
    }

    dats_node_t *penultimate = _get_node(self->head, self->length - 2);

    void *data = _free_node(penultimate->next_node);

    penultimate->next_node = NULL;
    self->tail = penultimate;
    self->length--;
    return data;
}

void *dats_linked_list_remove_index(dats_linked_list_t *self, uint64_t index)
{
    assert(index < self->length);

    if (index == 0)
    {
        return dats_linked_list_remove_head(self);
    }
    else if (index == self->length - 1)
    {
        return dats_linked_list_remove_tail(self);
    }

    dats_node_t *previous_node_from_index = _get_node(self->head, index-1);
    dats_node_t *following_node_from_index = previous_node_from_index->next_node->next_node;
    
    void *data = _free_node(previous_node_from_index->next_node);
    previous_node_from_index->next_node = following_node_from_index;
    self->length--;
    
    return data;
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

uint64_t dats_linked_list_length(const dats_linked_list_t *self)
{
    return self->length;
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

static dats_node_t *_alloc_node(uint64_t data_size)
{
    dats_node_t *node = malloc(sizeof(dats_node_t));
    node->data = malloc(data_size);
    node->next_node = NULL;
    return node;
}

static void *_free_node(dats_node_t *node_to_free)
{
    // free(node_to_free->data);
    // node_to_free->data = NULL;
    void *data = node_to_free->data;
    free(node_to_free);
    node_to_free = NULL;
    return data;
}

static dats_node_t *_get_node(dats_node_t *start, uint64_t index)
{
    for (uint64_t i = 0; i < index; i++)
    {
        start = start->next_node;
    }
    return start;
}