#include <stdint.h>
#include <stdlib.h>

#include "linked_list.h"

typedef struct _dats_linked_list_t
{
    uint64_t id;
} dats_linked_list_t;

dats_linked_list_t *dats_linked_list_new()
{
    dats_linked_list_t *ll = malloc(sizeof(dats_linked_list_t));
    ll->id = 111;
    return ll;
}

void dats_linked_list_free(dats_linked_list_t *self)
{
    free(self);
}
