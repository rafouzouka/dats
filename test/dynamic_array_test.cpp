#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include <stdint.h>

extern "C"
{
    #include "../src/dats.h"

    typedef struct
    {
        uint64_t x;
        uint64_t y;
    } _Fake_Position;
}

TEST(dats_dynamic_array_new, CreateADynamicArray)
{
    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(double));

    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 0);
    EXPECT_EQ(da.data_size, sizeof(double));
    EXPECT_NE(da.buffer, nullptr);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_add, AddEmptyWithEnoughCapacity)
{
    _Fake_Position data1 = { 111, 1111 };

    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    EXPECT_EQ(da.capacity, 1);
    EXPECT_EQ(da.length, 0);
    EXPECT_NE(da.buffer, nullptr);

    dats_dynamic_array_add(&da, &data1);

    const _Fake_Position *res = (const _Fake_Position*)dats_dynamic_array_get(&da, 0);
    EXPECT_EQ(res->x, data1.x);
    EXPECT_EQ(res->y, data1.y);
    EXPECT_EQ(da.capacity, 1);
    EXPECT_EQ(da.length, 1);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_add, AddEmptyWithoutEnoughCapacity)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };

    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    EXPECT_EQ(da.capacity, 1);
    EXPECT_EQ(da.length, 0);
    EXPECT_NE(da.buffer, nullptr);

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);

    const _Fake_Position *res = (const _Fake_Position*)dats_dynamic_array_get(&da, 0);
    EXPECT_EQ(res->x, data1.x);
    EXPECT_EQ(res->y, data1.y);

    const _Fake_Position *res2 = (const _Fake_Position*)dats_dynamic_array_get(&da, 1);
    EXPECT_EQ(res2->x, data2.x);
    EXPECT_EQ(res2->y, data2.y);

    EXPECT_EQ(da.capacity, 2);
    EXPECT_EQ(da.length, 2);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_add, TestAutomaticCapacityGrowth)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };
    _Fake_Position data3 = { 333, 3333 };
    _Fake_Position data4 = { 444, 4444 };

    dats_dynamic_array_t da = dats_dynamic_array_new(3, sizeof(_Fake_Position));

    EXPECT_EQ(da.capacity, 3);
    EXPECT_EQ(da.length, 0);
    EXPECT_NE(da.buffer, nullptr);

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);
    dats_dynamic_array_add(&da, &data3);

    EXPECT_EQ(da.capacity, 3);
    EXPECT_EQ(da.length, 3);

    dats_dynamic_array_add(&da, &data4);

    EXPECT_EQ(da.capacity, 6);
    EXPECT_EQ(da.length, 4);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_remove, RemoveOneItemArray)
{
    _Fake_Position data1 = { 111, 1111 };

    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 1);

    dats_dynamic_array_remove(&da, &data1);
    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 0);

    dats_dynamic_array_add(&da, &data1);
    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 1);

    const _Fake_Position *res = (const _Fake_Position *)dats_dynamic_array_get(&da, 0);
    EXPECT_EQ(res->x, data1.x);
    EXPECT_EQ(res->y, data1.y);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_remove, RemoveOneItemInThreeSlotArray)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };
    _Fake_Position data3 = { 333, 3333 };

    dats_dynamic_array_t da = dats_dynamic_array_new(2, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);
    dats_dynamic_array_add(&da, &data3);
    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 3);


    dats_dynamic_array_remove(&da, &data2);
    EXPECT_EQ(da.capacity, 4);
    EXPECT_EQ(da.length, 2);

    const _Fake_Position *res1 = (const _Fake_Position *)dats_dynamic_array_get(&da, 0);
    EXPECT_EQ(res1->x, data1.x);
    EXPECT_EQ(res1->y, data1.y);

    const _Fake_Position *res2 = (const _Fake_Position *)dats_dynamic_array_get(&da, 1);
    EXPECT_EQ(res2->x, data3.x);
    EXPECT_EQ(res2->y, data3.y);

    dats_dynamic_array_free(&da);
}

static void _test_MapOneItemArray(const void *data)
{
    const _Fake_Position *res = (const _Fake_Position*)data;
    EXPECT_EQ(res->x, 111);
    EXPECT_EQ(res->y, 1111);
}

TEST(dats_dynamic_array_map, MapOneItemArray)
{
    _Fake_Position data1 = { 111, 1111 };
    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));
    dats_dynamic_array_add(&da, &data1);

    dats_dynamic_array_map(&da, _test_MapOneItemArray);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_get, GetTwoItemData)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };

    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);

    EXPECT_EQ(da.capacity, 2);
    EXPECT_EQ(da.length, 2);

    const _Fake_Position *res = (const _Fake_Position*)dats_dynamic_array_get(&da, 0);
    EXPECT_EQ(res->x, data1.x);
    EXPECT_EQ(res->y, data1.y);
    EXPECT_EQ(res, da.buffer);

    const _Fake_Position *res2 = (const _Fake_Position*)dats_dynamic_array_get(&da, 1);
    EXPECT_EQ(res2->x, data2.x);
    EXPECT_EQ(res2->y, data2.y);

    uint8_t *buffer = (uint8_t *)da.buffer; 
    EXPECT_EQ((const void *)res2, (const void *)&buffer[1 * da.data_size]);

    EXPECT_EQ(da.capacity, 2);
    EXPECT_EQ(da.length, 2);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_find_index, FindIndexWithDataThatExists)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };

    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);

    EXPECT_EQ(1, dats_dynamic_array_find_index(&da, &data2));
    EXPECT_EQ(0, dats_dynamic_array_find_index(&da, &data1));

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_length, EmptyArray)
{
    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    EXPECT_EQ(0, dats_dynamic_array_length(&da));

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_length, TwoItemArray)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };

    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);

    EXPECT_EQ(2, dats_dynamic_array_length(&da));

    dats_dynamic_array_remove(&da, &data2);

    EXPECT_EQ(1, dats_dynamic_array_length(&da));

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_clear, ClearEmptyArray)
{
    dats_dynamic_array_t da = dats_dynamic_array_new(1, sizeof(_Fake_Position));
    EXPECT_EQ(0, da.length);
    EXPECT_EQ(1, da.capacity);

    dats_dynamic_array_clear(&da);
    EXPECT_EQ(0, da.length);
    EXPECT_EQ(1, da.capacity);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_clear, ClearMultipleOperationArray)
{
    _Fake_Position data1 = { 111, 1111 };
    _Fake_Position data2 = { 222, 2222 };

    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(_Fake_Position));

    dats_dynamic_array_add(&da, &data1);
    dats_dynamic_array_add(&da, &data2);
    EXPECT_EQ(2, da.length);
    EXPECT_EQ(4, da.capacity);

    dats_dynamic_array_clear(&da);
    EXPECT_EQ(0, da.length);
    EXPECT_EQ(4, da.capacity);

    dats_dynamic_array_free(&da);
}

TEST(dats_dynamic_array_free, FreeEmptyDynamicArray)
{
    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(int));

    dats_dynamic_array_free(&da);

    EXPECT_EQ(da.capacity, 0);
    EXPECT_EQ(da.length, 0);
    EXPECT_EQ(da.buffer, nullptr);
    EXPECT_EQ(da.data_size, sizeof(int));
}