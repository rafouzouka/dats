#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

extern "C"
{
    #include "../src/dats.h"
}

// c'est bien de tester les asserts

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

// essayer de chopper une valeur avant puis apr_s
TEST(dats_linked_list_free, FreeingOneItemLinkedList)
{
    long data = 5555;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(long));
    dats_linked_list_insert_head(&ll, &data);

    dats_linked_list_free(&ll);

    EXPECT_EQ(ll.head, nullptr);
    EXPECT_EQ(ll.tail, nullptr);
    EXPECT_EQ(ll.length, 0);
}

TEST(dats_linked_list_get, GetDataFromOneNodeInLinkedList)
{
    long long data = 99999;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(long long));

    dats_linked_list_insert_head(&ll, &data);
    const long long *ptr = (long long*)dats_linked_list_get(&ll, 0);

    EXPECT_EQ(data, *ptr);
    EXPECT_NE(&data, ptr);

    dats_linked_list_free(&ll);
}

TEST(dats_linked_list_get, IndexParamOutOfRange)
{
    long long data = 99999;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(long long));

    dats_linked_list_insert_head(&ll, &data);

    EXPECT_DEATH(dats_linked_list_get(&ll, 10), "Assertion");

    dats_linked_list_free(&ll);
}

TEST(dats_linked_list_insert_tail, InsertToEmptyLinkedList)
{
    short int data = 128;
    dats_linked_list_t ll = dats_linked_list_new(sizeof(short int));

    dats_linked_list_insert_tail(&ll, &data);

    EXPECT_EQ(ll.head, ll.tail);
    EXPECT_EQ(*((short int*)ll.head->data), data);
    EXPECT_EQ(*((short int*)ll.tail->data), data);

    EXPECT_EQ(ll.length, 1);
    EXPECT_EQ(ll.data_size, sizeof(short int));
    dats_linked_list_free(&ll);
}

TEST(dats_linked_list_insert_tail, InsertToOneNodesLinkedList)
{
    unsigned int data1 = 1111;
    unsigned int data2 = 2222;
    
    dats_linked_list_t ll = dats_linked_list_new(sizeof(unsigned int));

    dats_linked_list_insert_tail(&ll, &data1);
    dats_linked_list_insert_tail(&ll, &data2);

    EXPECT_NE(ll.tail, ll.head);
    EXPECT_EQ(*((unsigned int*)ll.head->data), data1);
    EXPECT_EQ(*((unsigned int*)ll.tail->data), data2);

    EXPECT_EQ(ll.length, 2);
    EXPECT_EQ(ll.data_size, sizeof(unsigned int));
    dats_linked_list_free(&ll);
}

TEST(dats_linked_list_insert_tail, InsertToTwoNodesLinkedList)
{
    unsigned int data1 = 1111;
    unsigned int data2 = 2222;
    unsigned int data3 = 3333;
    
    dats_linked_list_t ll = dats_linked_list_new(sizeof(unsigned int));
    dats_linked_list_insert_tail(&ll, &data1);
    dats_linked_list_insert_head(&ll, &data2);

    dats_linked_list_insert_tail(&ll, &data3);

    EXPECT_EQ(*((unsigned int*)ll.head->data), data2);
    EXPECT_EQ(*((unsigned int*)dats_linked_list_get(&ll, 1)), data1);
    EXPECT_EQ(*((unsigned int*)ll.tail->data), data3);
    EXPECT_NE(ll.tail, ll.head);

    EXPECT_EQ(ll.length, 3);
    EXPECT_EQ(ll.data_size, sizeof(unsigned int));
    dats_linked_list_free(&ll);
}

static void _test_MapToOneNodeLinkedList(const void *data)
{
    EXPECT_EQ(*((const int*)data), 1111);
}

TEST(dats_linked_list_map, MapToOneNodeLinkedList)
{
    int data1 = 1111;

    dats_linked_list_t ll = dats_linked_list_new(sizeof(int));
    dats_linked_list_insert_tail(&ll, &data1);

    dats_linked_list_map(&ll, _test_MapToOneNodeLinkedList);

    dats_linked_list_free(&ll);
}