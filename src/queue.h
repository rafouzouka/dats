#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#include "linked_list.h"

typedef struct
{
    dats_linked_list_t ll;
} dats_queue_t;

dats_queue_t dats_queue_new(uint64_t data_size);

void dats_queue_enqueue(dats_queue_t *self, const void *data);

void *dats_queue_dequeue(dats_queue_t *self);

void dats_queue_map(const dats_queue_t *self, void (*func)(const void*data));

void dats_queue_free(dats_queue_t *self);

#endif