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

TEST(dats_dense_array_new, CreateSimpleTypeDenseArray)
{
    dats_dense_array_t da = dats_dense_array_new(sizeof(int));

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(sizeof(int), da.data_size);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_new, CreateFakePositionDenseArray)
{
    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(sizeof(_Fake_Position), da.data_size);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_free, FreeEmptyDenseArray)
{
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_free(&da);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(sizeof(double), da.data_size);
}

TEST(dats_dense_array_free, FreeSimpleTypeDenseArray)
{
    double data1 = 125.8;
    double data2 = 225.8;
    double data3 = 325.8;

    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 0, &data1);
    dats_dense_array_insert(&da, 1, &data1);
    dats_dense_array_insert(&da, 10, &data1);

    EXPECT_EQ(3, da.data_length);
    EXPECT_EQ(3, da.lookup_length);
    EXPECT_EQ(sizeof(double), da.data_size);

    dats_dense_array_free(&da);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(sizeof(double), da.data_size);
}

TEST(dats_dense_array_free, FreeFakePositionDenseArray)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };
    _Fake_Position pos2 = { .x = 2, .y = 22 };
    _Fake_Position pos3 = { .x = 3, .y = 33 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    dats_dense_array_insert(&da, 5, &pos1);
    dats_dense_array_insert(&da, 3, &pos2);
    dats_dense_array_insert(&da, 8, &pos3);

    dats_dense_array_free(&da);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(0, da.data_size);
}