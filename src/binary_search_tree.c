#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "binary_search_tree.h"

static dats_node_tree_t *_alloc_node_tree(uint64_t data_size);
static dats_node_tree_t *_create_node_tree(uint64_t data_size, const void *data);

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

static dats_node_tree_t *_insert_node_tree(const dats_binary_search_tree_t *self, dats_node_tree_t *node, const void *data)
{
    if (node == NULL)
    {
        node = _create_node_tree(self->data_size, data);
        return node;
    }

    // peut etre ici ajouter une condition quand la valeur est la meme
    if (self->compare(data, node) < 0)
    {
        node->left = _insert_node_tree(self, node->left, data);
    }
    else
    {
        node->left = _insert_node_tree(self, node->right, data);
    }

    return node;
}

void dats_binary_search_tree_insert(dats_binary_search_tree_t *self, const void *data)
{
    self->head = _insert_node_tree(self, self->head, data);
    self->length++;
}

void dats_binary_search_tree_free(dats_binary_search_tree_t *self)
{
    // free memory before here
    free(self->head->data);
    self->head->data = NULL;
    free(self->head);

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
