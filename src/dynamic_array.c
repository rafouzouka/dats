#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynamic_array.h"

static void *_get_data_ptr(const dats_dynamic_array_t *self, uint64_t index);
static void _ensure_capacity(dats_dynamic_array_t *self, uint64_t asked_capacity);

dats_dynamic_array_t dats_dynamic_array_new(uint64_t capacity, uint64_t data_size)
{
    dats_dynamic_array_t da = {
        .data_size = data_size,
        .length = 0,
        .capacity = capacity,
        .buffer = calloc(capacity, data_size)
    };
    return da;
}

// void dats_dynamic_array_insert(dats_dynamic_array_t *self, uint64_t index, const void *data)
// {

// }

void dats_dynamic_array_add(dats_dynamic_array_t *self, const void *data)
{
    _ensure_capacity(self, self->length + 1);

    memcpy(_get_data_ptr(self, self->length), data, self->data_size);
    self->length++;
}

// voir ce que ça donne quand l'array est de taille 1
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

    return _get_data_ptr(self, index);
}

uint64_t dats_dynamic_array_find_index(const dats_dynamic_array_t *self, const void *data)
{
    assert(self->length > 0);

    for (uint64_t i = 0; i < self->length; i++)
    {
        const void *item = _get_data_ptr(self, i);

        if (memcmp(item, data, self->data_size) == 0)
        {
            return i;
        }
    }

    fprintf(stderr, "[ERROR]: Unable to find the data in file: %s at line: %d.\n", __FILE__, __LINE__);
    exit(EXIT_FAILURE);
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

    self->buffer = realloc(self->buffer, self->capacity * 2 * self->data_size);

    memset(_get_data_ptr(self, self->capacity), 0, self->capacity * self->data_size);
    self->capacity *= 2;
}

static void *_get_data_ptr(const dats_dynamic_array_t *self, uint64_t index)
{
    uint8_t *buffer = self->buffer;
    return &buffer[index * self->data_size];
}