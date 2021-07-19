#include <stdlib.h>

#include "binary_search_tree.h"

dats_binary_search_tree_t dats_binary_search_tree_new(uint64_t data_size)
{
    dats_binary_search_tree_t bst = {
        .head = NULL,
        .data_size = data_size,
        .length = 0
    };
    return bst;
}

void dats_binary_search_tree_free(dats_binary_search_tree_t *self)
{
    // free memory before here
    self->head = NULL;
    self->length = 0;
}
