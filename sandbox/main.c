#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

int main()
{
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    int a = 10;
    int b = 125;

    dats_linked_list_insert_head(&ll, &a);
    dats_linked_list_insert_head(&ll, &b);

    dats_linked_list_free(&ll);
    return EXIT_SUCCESS;
}