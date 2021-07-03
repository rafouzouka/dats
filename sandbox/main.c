#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

typedef struct {
    int64_t x;
    int64_t y;
} Position;

// static void fn(const void* d)
// {
//     const double *data = d;
//     printf("data -> %f\n", *data);
// }

int main()
{
    Position data1 = { 1234561, 6543211 };
    Position data2 = { 1234562, 6543212 };
    // // Position data3 = { 33, 33333 };

    dats_queue_t queue = dats_queue_new(sizeof(Position));

    dats_queue_enqueue(&queue, &data1);
    dats_queue_enqueue(&queue, &data2);

    Position *res = dats_queue_dequeue(&queue);
    printf("x: %ld, %ld\n", res->x, res->y);

    free(res);
    dats_queue_free(&queue);
    return EXIT_SUCCESS;
}