#include <stdlib.h>

#include "linked_list.h"

dats_linked_list_t dats_linked_list_new(const uint64_t data_size)
{
    dats_linked_list_t ll = {
        .head = NULL,
        .tail = NULL,
        .data_size = data_size,
        .length = 0
    };
    return ll;
}

void dats_linked_list_free(dats_linked_list_t *self)
{
    self->length = 1;
}
