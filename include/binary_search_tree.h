#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdint.h>

typedef struct _dats_node_tree_t dats_node_tree_t;

typedef struct _dats_node_tree_t
{
    void *data;
    dats_node_tree_t *left;
    dats_node_tree_t *right;
} dats_node_tree_t;

typedef struct
{
    dats_node_tree_t *head;
    int64_t (*compare)(const void *a, const void *b);
    uint64_t length;
    const uint64_t data_size;
} dats_binary_search_tree_t;

dats_binary_search_tree_t dats_binary_search_tree_new(uint64_t data_size, int64_t (*compare)(const void *a, const void *b));

void dats_binary_search_tree_insert(dats_binary_search_tree_t *self, const void *data);

void dats_binary_search_tree_remove(dats_binary_search_tree_t *self, const void *data);

void dats_binary_search_tree_to_array(const dats_binary_search_tree_t *self, void **arr);

uint64_t dats_binary_search_tree_length(const dats_binary_search_tree_t *self);

void dats_binary_search_tree_free(dats_binary_search_tree_t *self);

#endif