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
    Position data1 = { 11, 22 };
    Position data2 = { 444, 888 };
    Position data3 = { 99, 999 };

    dats_stack_t s = dats_stack_new(sizeof(Position));
    dats_stack_push(&s, &data1);
    dats_stack_push(&s, &data2);
    dats_stack_push(&s, &data3);

    Position *res = dats_stack_pop(&s);
    printf("Position -> x: %ld, y: %ld\n", res->x, res->y);
    free(res);

    Position *res2 = dats_stack_pop(&s);
    printf("Position -> x: %ld, y: %ld\n", res2->x, res2->y);
    free(res2);

    Position *res3 = dats_stack_pop(&s);
    printf("Position -> x: %ld, y: %ld\n", res3->x, res3->y);
    free(res3);

    dats_stack_free(&s);
    return EXIT_SUCCESS;
}