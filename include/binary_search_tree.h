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
    uint64_t length;
    const uint64_t data_size;
} dats_binary_search_tree_t;

dats_binary_search_tree_t dats_binary_search_tree_new();

void dats_binary_search_tree_free(dats_binary_search_tree_t *self);

#endif