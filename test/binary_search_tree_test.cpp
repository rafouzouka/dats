#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include <stdint.h>

extern "C"
{
    #include <dats/dats.h>

    typedef struct
    {
        uint64_t x;
        uint64_t y;
    } _Fake_Position;
}

static int64_t _compare_int(const void* a, const void *b)
{
    if (*((int*)a) > *((int*)b))
    {
        return 1;
    }
    else if (*((int*)a) < *((int*)b))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

static int64_t _compare_fake_position(const void* a, const void *b)
{
    if (((_Fake_Position*)a)->x > ((_Fake_Position*)b)->x)
    {
        return 1;
    }
    else if (((_Fake_Position*)a)->x < ((_Fake_Position*)b)->x)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

TEST(dats_binary_search_tree_new, CreateBinarySearchTreeBasicType)
{
    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(int), _compare_int);

    EXPECT_EQ(bst.compare, _compare_int);
    EXPECT_EQ(bst.data_size, sizeof(int));
    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_new, CreateBinarySearchTreeStructType)
{
    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    EXPECT_EQ(bst.compare, _compare_fake_position);
    EXPECT_EQ(bst.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_insert, InsertInEmptyBST)
{
    _Fake_Position data = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);

    dats_binary_search_tree_insert(&bst, &data);    

    EXPECT_NE(bst.head, nullptr);
    EXPECT_EQ(bst.length, 1);

    dats_binary_search_tree_insert(&bst, &data2);    

    EXPECT_NE(bst.head, nullptr);
    EXPECT_EQ(bst.length, 2);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_free, FreeEmptyBST)
{
    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_free(&bst);

    EXPECT_EQ(bst.compare, nullptr);
    EXPECT_EQ(bst.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);
}

TEST(dats_binary_search_tree_free, MultipleItemBST)
{
    _Fake_Position data = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };
    _Fake_Position data3 = { .x = 30, .y = 35 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);
    dats_binary_search_tree_insert(&bst, &data);    
    dats_binary_search_tree_insert(&bst, &data2);    
    dats_binary_search_tree_insert(&bst, &data3);    

    dats_binary_search_tree_free(&bst);

    EXPECT_EQ(bst.compare, nullptr);
    EXPECT_EQ(bst.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);
}