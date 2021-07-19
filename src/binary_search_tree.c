#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#include "queue.h"
#include "utils.h"
#include "binary_search_tree.h"

static dats_node_tree_t *_alloc_node_tree(uint64_t data_size);
static dats_node_tree_t *_create_node_tree(uint64_t data_size, const void *data);
static dats_node_tree_t *_insert_node_tree(const dats_binary_search_tree_t *self, dats_node_tree_t *node, const void *data);
static void _postorder_traversal(dats_node_tree_t *node, void (*func)(dats_node_tree_t *node));

dats_binary_search_tree_t dats_binary_search_tree_new(uint64_t data_size, int64_t (*compare)(const void *a, const void *b))
{
    dats_binary_search_tree_t bst = {
        .head = NULL,
        .compare = compare,
        .data_size = data_size,
        .length = 0
    };
    return bst;
}

void dats_binary_search_tree_insert(dats_binary_search_tree_t *self, const void *data)
{
    self->head = _insert_node_tree(self, self->head, data);
    self->length++;
}

void _print_func(dats_node_tree_t *node)
{
    printf("[%d] ", *((int*)node->data));
}

void dats_binary_search_tree_print(const dats_binary_search_tree_t *self)
{
    _postorder_traversal(self->head, _print_func);
}

static void _free_node_tree(dats_node_tree_t *node)
{
    free(node->data);
    node->left = NULL;
    node->right = NULL;
    node->data = NULL;
    free(node);
}

void dats_binary_search_tree_free(dats_binary_search_tree_t *self)
{
    _postorder_traversal(self->head, _free_node_tree);

    self->compare = NULL;
    self->head = NULL;
    self->length = 0;
}

static dats_node_tree_t *_create_node_tree(uint64_t data_size, const void *data)
{
    dats_node_tree_t *nt = _alloc_node_tree(data_size);
    memcpy(nt->data, data, data_size);
    return nt;
}

static dats_node_tree_t *_alloc_node_tree(uint64_t data_size)
{
    dats_node_tree_t *nt = DATS_OOM_GUARD(malloc(sizeof(dats_node_tree_t)));
    nt->data = DATS_OOM_GUARD(malloc(data_size));
    nt->left = NULL;
    nt->right = NULL;
    return nt;
}

static void _postorder_traversal(dats_node_tree_t *node, void (*func)(dats_node_tree_t *node))
{
    if (node == NULL)
    {
        return;
    }
    _postorder_traversal(node->left, func);
    _postorder_traversal(node->right, func);
    func(node);
}

static dats_node_tree_t *_insert_node_tree(const dats_binary_search_tree_t *self, dats_node_tree_t *node, const void *data)
{
    if (node == NULL)
    {
        node = _create_node_tree(self->data_size, data);
        return node;
    }

    switch (self->compare(data, node->data))
    {
        case -1:
            node->left = _insert_node_tree(self, node->left, data);
            break;

        case 1:
            node->right = _insert_node_tree(self, node->right, data);
            break;

        default:
            DATS_RAISE_ERROR("This BST doesn't accept duplicate data or compare function isn't implemented correctly.");
            break;
    }

    return node;
}