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

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    EXPECT_EQ(bst.head, nullptr);
    EXPECT_EQ(bst.length, 0);

    dats_binary_search_tree_insert(&bst, &data);    

    EXPECT_NE(bst.head, nullptr);
    EXPECT_EQ(bst.length, 1);

    void *arr[dats_binary_search_tree_length(&bst)];
    dats_binary_search_tree_to_array(&bst, arr);

    EXPECT_EQ(data.x, ((_Fake_Position*)arr[0])->x);
    EXPECT_EQ(data.y, ((_Fake_Position*)arr[0])->y);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_insert, InsertLeftToRightInBST)
{
    _Fake_Position data1 = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };
    _Fake_Position data3 = { .x = 30, .y = 35 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data1);    
    dats_binary_search_tree_insert(&bst, &data2);    
    dats_binary_search_tree_insert(&bst, &data3);    

    EXPECT_EQ(bst.length, 3);

    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data1.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->data)->x, data2.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->right->data)->x, data3.x);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_insert, InsertTwoDepthInBST)
{
    _Fake_Position data1 = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 30, .y = 35 };
    _Fake_Position data3 = { .x = 20, .y = 25 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data1);    
    dats_binary_search_tree_insert(&bst, &data2);    
    dats_binary_search_tree_insert(&bst, &data3);    

    EXPECT_EQ(bst.length, 3);

    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data1.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->data)->x, data2.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->left->data)->x, data3.x);

    dats_binary_search_tree_free(&bst);
}


TEST(dats_binary_search_tree_insert, VerifyPositionOfNodesInBST)
{
    int arr[] = { 5, 4, 7, 3, 6, 8 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(int), _compare_int);
    
    dats_binary_search_tree_insert(&bst, &arr[0]);
    dats_binary_search_tree_insert(&bst, &arr[1]);
    dats_binary_search_tree_insert(&bst, &arr[3]);
    dats_binary_search_tree_insert(&bst, &arr[2]);
    dats_binary_search_tree_insert(&bst, &arr[5]);
    dats_binary_search_tree_insert(&bst, &arr[4]);

    void *arr_result[dats_binary_search_tree_length(&bst)];
    dats_binary_search_tree_to_array(&bst, arr_result);

    EXPECT_EQ(arr[0], *((int*)arr_result[0]));
    EXPECT_EQ(arr[1], *((int*)arr_result[1]));
    EXPECT_EQ(arr[2], *((int*)arr_result[2]));
    EXPECT_EQ(arr[3], *((int*)arr_result[3]));
    EXPECT_EQ(arr[4], *((int*)arr_result[4]));
    EXPECT_EQ(arr[5], *((int*)arr_result[5]));

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_remove, RemoveWithoutImpactOnBSTLayout)
{
    _Fake_Position data1 = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data1);
    dats_binary_search_tree_insert(&bst, &data2);
    EXPECT_EQ(2, bst.length);

    dats_binary_search_tree_remove(&bst, &data2);
    EXPECT_EQ(1, bst.length);

    EXPECT_NE((_Fake_Position*)bst.head, nullptr);
    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data1.x);
    EXPECT_EQ((_Fake_Position*)bst.head->right, nullptr);
    EXPECT_EQ((_Fake_Position*)bst.head->left, nullptr);

    dats_binary_search_tree_remove(&bst, &data1);
    EXPECT_EQ(0, bst.length);
    EXPECT_EQ((_Fake_Position*)bst.head, nullptr);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_remove, RemoveNodeWithSimpleSwap)
{
    _Fake_Position data1 = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };
    _Fake_Position data3 = { .x = 30, .y = 35 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data1);
    dats_binary_search_tree_insert(&bst, &data2);
    dats_binary_search_tree_insert(&bst, &data3);
    EXPECT_EQ(3, bst.length);

    dats_binary_search_tree_remove(&bst, &data2);
    EXPECT_EQ(2, bst.length);

    EXPECT_NE((_Fake_Position*)bst.head, nullptr);
    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data1.x);
    EXPECT_EQ((_Fake_Position*)bst.head->left, nullptr);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->data)->x, data3.x);

    dats_binary_search_tree_remove(&bst, &data1);
    EXPECT_EQ(1, bst.length);
    EXPECT_NE((_Fake_Position*)bst.head, nullptr);
    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data3.x);
    EXPECT_EQ((_Fake_Position*)bst.head->left, nullptr);
    EXPECT_EQ((_Fake_Position*)bst.head->right, nullptr);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_remove, RemoveNodeWithDeepSwapRight)
{
    _Fake_Position data1 = { .x = 20, .y = 25 };
    _Fake_Position data2 = { .x = 10, .y = 15 };
    _Fake_Position data3 = { .x = 30, .y = 35 };
    _Fake_Position data4 = { .x = 25, .y = 25252525 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data1);
    dats_binary_search_tree_insert(&bst, &data2);
    dats_binary_search_tree_insert(&bst, &data3);
    dats_binary_search_tree_insert(&bst, &data4);
    EXPECT_EQ(4, bst.length);

    dats_binary_search_tree_remove(&bst, &data1);
    EXPECT_EQ(3, bst.length);

    EXPECT_EQ(((_Fake_Position*)bst.head->data)->x, data4.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->left->data)->x, data2.x);
    EXPECT_EQ(((_Fake_Position*)bst.head->right->data)->x, data3.x);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_to_array, TwoNodesBST)
{
    _Fake_Position data = { .x = 10, .y = 15 };
    _Fake_Position data2 = { .x = 20, .y = 25 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    dats_binary_search_tree_insert(&bst, &data);
    dats_binary_search_tree_insert(&bst, &data2);

    void *arr[dats_binary_search_tree_length(&bst)];
    dats_binary_search_tree_to_array(&bst, arr);

    EXPECT_EQ(bst.length, 2);
    EXPECT_EQ(data.x, ((_Fake_Position*)arr[0])->x);
    EXPECT_EQ(data.y, ((_Fake_Position*)arr[0])->y);

    EXPECT_EQ(data2.x, ((_Fake_Position*)arr[1])->x);
    EXPECT_EQ(data2.y, ((_Fake_Position*)arr[1])->y);

    dats_binary_search_tree_free(&bst);
}

TEST(dats_binary_search_tree_length, ManipulatedBST)
{
    _Fake_Position data = { .x = 10, .y = 15 };
    // _Fake_Position data2 = { .x = 20, .y = 25 };

    dats_binary_search_tree_t bst = dats_binary_search_tree_new(sizeof(_Fake_Position), _compare_fake_position);

    EXPECT_EQ(0, dats_binary_search_tree_length(&bst));

    dats_binary_search_tree_insert(&bst, &data);

    EXPECT_EQ(1, dats_binary_search_tree_length(&bst));

    dats_binary_search_tree_remove(&bst, &data);

    EXPECT_EQ(0, dats_binary_search_tree_length(&bst));

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