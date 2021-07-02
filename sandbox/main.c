#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

int main()
{
    int data = 15;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    dats_linked_list_insert_head(&ll, &data);

    dats_linked_list_get_data(&ll, 0);

    dats_linked_list_free(&ll);
    return 0;
}