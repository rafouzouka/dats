#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

int main()
{
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    dats_linked_list_free(&ll);
    return EXIT_SUCCESS;
}