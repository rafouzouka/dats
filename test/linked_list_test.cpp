#include <gtest/gtest.h>

extern "C"
{
    #include "../src/dats.h"
}

TEST(dats_linked_list_new, CreateAnEmptyLinkedList) {
  
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    EXPECT_EQ(ll.head, nullptr);
    EXPECT_EQ(ll.tail, nullptr);
    EXPECT_EQ(ll.data_size, sizeof(int));
    EXPECT_EQ(ll.length, 0);
}
