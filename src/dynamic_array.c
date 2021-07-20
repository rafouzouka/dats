#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynamic_array.h"
#include "utils.h"

static void *_get_data_ptr(dats_dynamic_array_t *self, uint64_t index);
static void _ensure_capacity(dats_dynamic_array_t *self, uint64_t asked_capacity);

dats_dynamic_array_t dats_dynamic_array_new(uint64_t capacity, uint64_t data_size)
{
    assert(data_size > 0);

    dats_dynamic_array_t da = {
        .data_size = data_size,
        .length = 0,
        .capacity = capacity,
        .buffer = DATS_OOM_GUARD(malloc(capacity * data_size))
    };
    return da;
}

void dats_dynamic_array_insert(dats_dynamic_array_t *self, uint64_t index, const void *data)
{
    assert(index < self->length);

    void *place_to_put_data = _get_data_ptr(self, index);
    memcpy(place_to_put_data, data, self->data_size);
}

void dats_dynamic_array_add(dats_dynamic_array_t *self, const void *data)
{
    _ensure_capacity(self, self->length + 1);

    memcpy(_get_data_ptr(self, self->length), data, self->data_size);
    self->length++;
}

void dats_dynamic_array_remove(dats_dynamic_array_t *self, const void *data)
{
    assert(self->length > 0);

    if (self->length == 1)
    {
        self->length--;
        return;
    }

    uint64_t index = dats_dynamic_array_find_index(self, data);
    memmove(_get_data_ptr(self, index), _get_data_ptr(self, index + 1), (self->length - index) * self->data_size);
    self->length--;
}

void dats_dynamic_array_map(const dats_dynamic_array_t *self, void (*func)(const void*))
{
    uint8_t *buffer = self->buffer;

    for (uint64_t i = 0; i < self->length; i++)
    {
        func(&buffer[i * self->data_size]);
    }
}

const void* dats_dynamic_array_get(const dats_dynamic_array_t *self, uint64_t index)
{
    assert(self->length > index);

    uint8_t *buffer = self->buffer;
    return &buffer[index * self->data_size];
}

bool dats_dynamic_array_contains(const dats_dynamic_array_t *self, const void *data)
{
    uint8_t *buffer = self->buffer; 

    for (uint64_t i = 0; i < self->length; i++)
    {
        if (memcmp(&buffer[i * self->data_size], data, self->data_size) == 0)
        {
            return true;
        }
    }

    return false;
}

uint64_t dats_dynamic_array_find_index(const dats_dynamic_array_t *self, const void *data)
{
    assert(self->length > 0);

    uint8_t *buffer = self->buffer; 

    for (uint64_t i = 0; i < self->length; i++)
    {
        if (memcmp(&buffer[i * self->data_size], data, self->data_size) == 0)
        {
            return i;
        }
    }

    DATS_RAISE_ERROR("Unable to find the data");
    exit(EXIT_FAILURE);
}

uint64_t dats_dynamic_array_length(const dats_dynamic_array_t *self)
{
    return self->length;
}

void dats_dynamic_array_clear(dats_dynamic_array_t *self)
{
    self->length = 0;
}

void dats_dynamic_array_free(dats_dynamic_array_t *self)
{
    self->capacity = 0;
    self->length = 0;
    
    free(self->buffer);
    self->buffer = NULL;
}

static void _ensure_capacity(dats_dynamic_array_t *self, uint64_t asked_capacity)
{
    if (asked_capacity <= self->capacity)
    {
        return;
    }

    self->buffer = DATS_OOM_GUARD(realloc(self->buffer, self->capacity * 2 * self->data_size));
    self->capacity *= 2;
}

static void *_get_data_ptr(dats_dynamic_array_t *self, uint64_t index)
{
    uint8_t *buffer = self->buffer;
    return &buffer[index * self->data_size];
}