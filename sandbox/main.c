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
//     const Position *data = d;

//     printf("Position -> x: %ld, y: %ld\n", data->x, data->y);
// }

int main()
{
    Position data1 = { 1234561, 6543211 };
    Position data2 = { 1234562, 6543212 };
    // // Position data3 = { 33, 33333 };

    dats_queue_t queue = dats_queue_new(sizeof(Position));

    dats_queue_enqueue(&queue, &data1);
    dats_queue_enqueue(&queue, &data2);

    dats_queue_free(&queue);

    return EXIT_SUCCESS;
}