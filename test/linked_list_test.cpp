#include <gtest/gtest.h>

extern "C"
{
    #include "../src/dats.h"
}

// faudrait aussi tester pour les types floattant double et float
// mais aussi les structs ou voir les unions

TEST(dats_linked_list_new, CreateAnEmptyLinkedList) {
  
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    EXPECT_EQ(ll.head, nullptr);
    EXPECT_EQ(ll.tail, nullptr);
    EXPECT_EQ(ll.data_size, sizeof(int));
    EXPECT_EQ(ll.length, 0);
}

TEST(dats_linked_list_insert_head, InsertNodeToEmptyLinkedList)
{
    dats_linked_list_t ll = dats_linked_list_new(sizeof(char));
    char data = 'd';

    dats_linked_list_insert_head(&ll, &data);
    
    EXPECT_EQ(*((char *)ll.head->data), data);
    EXPECT_NE(ll.head->data, &data) << "The parameter data and the data in the node must be copied.\
    We should not just copy the pointer to the data";

    EXPECT_EQ(*((char *)ll.tail->data), data) << "When the linked list is empty the head and the tail must be pointing to the same node.";
    EXPECT_NE(ll.tail->data, &data) << "The parameter data and the data in the node must be copied.\
    We should not just copy the pointer to the data";

    EXPECT_EQ(ll.length, 1);
    EXPECT_EQ(ll.data_size, sizeof(char));

    dats_linked_list_free(&ll);
}

TEST(dats_linked_list_insert_head, InsertNodeToAlreadyOneNodeLinkedList)
{
    int existindData = 555;
    int newData = 999;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));

    dats_linked_list_insert_head(&ll, &existindData);
    dats_linked_list_insert_head(&ll, &newData);

    EXPECT_NE(ll.head, ll.tail);
    EXPECT_EQ(*((int *)ll.tail->data), existindData);
    EXPECT_EQ(*((int *)ll.head->data), newData);

    EXPECT_EQ(ll.length, 2);
    EXPECT_EQ(ll.data_size, sizeof(int));

    dats_linked_list_free(&ll);
}

