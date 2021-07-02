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
    // Position pos1 = { 81, 581 };
    // Position pos2 = { 89832, 9654232 };
    // Position pos3 = { 333353, 23 };

    double pos1 = 128.1;
    double pos2 = 5645.2;
    double pos3 = 998.3;

    double pos4 = 998.300001;

    dats_linked_list_t ll = dats_linked_list_new(sizeof(double));
    printf("=====================================\n");

    dats_linked_list_insert_head(&ll, &pos1);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_insert_head(&ll, &pos2);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_insert_tail(&ll, &pos3);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_insert_tail(&ll, &pos4);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_remove_head(&ll);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_remove_head(&ll);
    dats_linked_list_map(&ll, fn);
    printf("=====================================\n");

    dats_linked_list_free(&ll);
    return 0;
}