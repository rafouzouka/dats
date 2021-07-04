#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

typedef struct {
    int64_t x;
    int64_t y;
} Position;

static void fn(const void* d)
{
    const Position *data = d;

    printf("[Position -> x: %ld, y: %ld]\n", data->x, data->y);
}

int main()
{
    Position data1 = { 11, 22 };
    Position data2 = { 444, 888 };
    Position data3 = { 999, 9999 };

    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(Position));

    dats_dynamic_array_map(&da, fn);

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);
    dats_dynamic_array_add(&da, &data2);
    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data3);
    dats_dynamic_array_add(&da, &data2);
    dats_dynamic_array_add(&da, &data2);

    dats_dynamic_array_map(&da, fn);
    printf("\n");

    dats_dynamic_array_remove(&da, &data3);

    dats_dynamic_array_map(&da, fn);
    printf("\n");

    dats_dynamic_array_add(&da, &data2);

    dats_dynamic_array_map(&da, fn);
    printf("\n");

    dats_dynamic_array_free(&da);
    
    return EXIT_SUCCESS;
}