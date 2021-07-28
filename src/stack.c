#include "stack.h"
#include "linked_list.h"

dats_stack_t dats_stack_new(uint64_t data_size)
{
    dats_stack_t s = {
        .ll = dats_linked_list_new(data_size)
    };
    return s;
}

void dats_stack_push(dats_stack_t *self, const void *data)
{
    dats_linked_list_insert_head(&self->ll, data);
}

void *dats_stack_pop(dats_stack_t *self)
{
    return dats_linked_list_remove_head(&self->ll);
}

const void *dats_stack_peek(const dats_stack_t *self)
{
    return dats_linked_list_get_head(&self->ll);
}

const void *dats_stack_get(const dats_stack_t *self, uint64_t index)
{
    return dats_linked_list_get(&self->ll, index);
}

bool dats_stack_contains(const dats_stack_t *self, const void *data)
{
    return dats_linked_list_contains(&self->ll, data);
}

uint64_t dats_stack_length(const dats_stack_t *self)
{
    return dats_linked_list_length(&self->ll);
}

void dats_stack_clear(dats_stack_t *self)
{
    dats_linked_list_clear(&self->ll);
}

void dats_stack_free(dats_stack_t *self)
{
    dats_linked_list_free(&self->ll);
}