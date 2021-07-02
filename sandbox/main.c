#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dats.h"

int main()
{
    unsigned int data1 = 1111;
    unsigned int data2 = 2222;
    unsigned int data3 = 3333;
    
    dats_linked_list_t ll = dats_linked_list_new(sizeof(unsigned int));
    dats_linked_list_insert_tail(&ll, &data1);
    dats_linked_list_insert_head(&ll, &data2);

    dats_linked_list_insert_tail(&ll, &data3);

    dats_linked_list_free(&ll);

    return 0;
}