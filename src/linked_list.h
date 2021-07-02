#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct _dats_linked_list_t dats_linked_list_t;

dats_linked_list_t *dats_linked_list_new();

void dats_linked_list_free(dats_linked_list_t *self);

#endif