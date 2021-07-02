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
    const double *data = d;
    printf("data -> %f\n", *data);
}

int main()
{
    Position data1 = { 1234561, 6543211 };
    Position data2 = { 1234562, 6543212 };
    Position data3 = { 33, 33333 };

    dats_linked_list_t ll = dats_linked_list_new(sizeof(Position));
    dats_linked_list_insert_head(&ll, &data1);
    dats_linked_list_insert_tail(&ll, &data2);
    dats_linked_list_insert_head(&ll, &data3);

    dats_linked_list_remove_tail(&ll);

    dats_linked_list_free(&ll);
    return 0;
}