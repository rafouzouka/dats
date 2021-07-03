#include "queue.h"

#include "linked_list.h"

dats_queue_t dats_queue_new(uint64_t data_size)
{
    dats_queue_t q = {
        .ll = dats_linked_list_new(data_size),
    };    
    return q;
}

void dats_queue_enqueue(dats_queue_t *self, const void *data)
{
    dats_linked_list_insert_head(&self->ll, data);
}

void *dats_queue_dequeue(dats_queue_t *self)
{
    return dats_linked_list_remove_tail(&self->ll);
}

const void *dats_queue_peek(const dats_queue_t *self)
{
    return dats_linked_list_get_tail(&self->ll);
}

const void *dats_queue_get(const dats_queue_t *self, uint64_t index)
{
    return dats_linked_list_get(&self->ll, index);
}

void dats_queue_map(const dats_queue_t *self, void (*func)(const void*data))
{
    dats_linked_list_map(&self->ll, func);
}

bool dats_queue_contains(const dats_queue_t *self, const void *data)
{
    return dats_linked_list_contains(&self->ll, data);
}

uint64_t dats_queue_length(const dats_queue_t *self)
{
    return dats_linked_list_length(&self->ll);
}

void dats_queue_free(dats_queue_t *self)
{
    dats_linked_list_free(&self->ll);
}
