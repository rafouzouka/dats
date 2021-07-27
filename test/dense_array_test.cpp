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

TEST(dats_dense_array_insert, InsertBasicFakePositionDenseArray)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };
    _Fake_Position pos2 = { .x = 2, .y = 22 };
    _Fake_Position pos3 = { .x = 3, .y = 33 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    dats_dense_array_insert(&da, 0, &pos1);
    dats_dense_array_insert(&da, 1, &pos2);
    dats_dense_array_insert(&da, 2, &pos3);

    EXPECT_EQ(pos1.x, ((_Fake_Position*)dats_dense_array_get(&da, 0))->x);
    EXPECT_EQ(pos2.x, ((_Fake_Position*)dats_dense_array_get(&da, 1))->x);
    EXPECT_EQ(pos3.x, ((_Fake_Position*)dats_dense_array_get(&da, 2))->x);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_insert, InsertWithSparseIndex)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };
    _Fake_Position pos2 = { .x = 2, .y = 22 };
    _Fake_Position pos3 = { .x = 3, .y = 33 };
    _Fake_Position pos4 = { .x = 4, .y = 44 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    dats_dense_array_insert(&da, 10, &pos1);
    dats_dense_array_insert(&da, 5, &pos2);
    dats_dense_array_insert(&da, 25, &pos3);
    dats_dense_array_insert(&da, 8, &pos4);

    EXPECT_EQ(pos1.x, ((_Fake_Position*)dats_dense_array_get(&da, 10))->x);
    EXPECT_EQ(pos2.x, ((_Fake_Position*)dats_dense_array_get(&da, 5))->x);
    EXPECT_EQ(pos3.x, ((_Fake_Position*)dats_dense_array_get(&da, 25))->x);
    EXPECT_EQ(pos4.x, ((_Fake_Position*)dats_dense_array_get(&da, 8))->x);
    EXPECT_EQ(26, da.lookup_length);
    EXPECT_EQ(4, da.data_length);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_insert, InsertWithBigSparseIndex)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };
    _Fake_Position pos2 = { .x = 2, .y = 22 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    dats_dense_array_insert(&da, 400, &pos1);
    dats_dense_array_insert(&da, 0, &pos2);

    EXPECT_EQ(pos1.x, ((_Fake_Position*)dats_dense_array_get(&da, 400))->x);
    EXPECT_EQ(pos2.x, ((_Fake_Position*)dats_dense_array_get(&da, 0))->x);
    EXPECT_EQ(401, da.lookup_length);
    EXPECT_EQ(2, da.data_length);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_remove, RemoveOneItemDenseArray)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));
    dats_dense_array_insert(&da, 10, &pos1);

    dats_dense_array_remove(&da, 10);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(11, da.lookup_length);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_remove, RemoveTwoItemDenseArray)
{
    _Fake_Position pos1 = { .x = 1, .y = 11 };
    _Fake_Position pos2 = { .x = 2, .y = 22 };
    _Fake_Position pos3 = { .x = 3, .y = 33 };
    _Fake_Position pos4 = { .x = 4, .y = 44 };

    dats_dense_array_t da = dats_dense_array_new(sizeof(_Fake_Position));

    dats_dense_array_insert(&da, 3, &pos1);
    dats_dense_array_insert(&da, 0, &pos2);
    dats_dense_array_insert(&da, 1, &pos3);

    EXPECT_EQ(4, da.lookup_length);
    EXPECT_EQ(3, da.data_length);

    dats_dense_array_remove(&da, 3);

    EXPECT_EQ(4, da.lookup_length);
    EXPECT_EQ(2, da.data_length);
    EXPECT_EQ(pos2.x, ((_Fake_Position*)dats_dense_array_get(&da, 0))->x);
    EXPECT_EQ(pos3.x, ((_Fake_Position*)dats_dense_array_get(&da, 1))->x);

    dats_dense_array_remove(&da, 1);

    EXPECT_EQ(4, da.lookup_length);
    EXPECT_EQ(1, da.data_length);
    EXPECT_EQ(pos2.x, ((_Fake_Position*)dats_dense_array_get(&da, 0))->x);

    dats_dense_array_remove(&da, 0);

    EXPECT_EQ(4, da.lookup_length);
    EXPECT_EQ(0, da.data_length);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_get, GetOneItemDenseArray)
{
    double data1 = 128.1;
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 5, &data1);

    EXPECT_EQ(data1, *((const double*)dats_dense_array_get(&da, 5)));

    dats_dense_array_free(&da);
}


TEST(dats_dense_array_ref, GetOneItemDenseArray)
{
    double data1 = 128.1;
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 5, &data1);

    EXPECT_EQ(data1, *((double*)dats_dense_array_ref(&da, 5)));

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_contains, DoesNotCotainsTheData)
{
    double data1 = 128.1;
    double data2 = 228.1;
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 5, &data1);

    EXPECT_TRUE(dats_dense_array_contains(&da, &data1));
    EXPECT_FALSE(dats_dense_array_contains(&da, &data2));

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_contains, AlterateDenseArray)
{
    double data1 = 128.1;
    double data2 = 228.1;
    double data3 = 328.1;
    double data4 = 428.1;
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 5, &data1);
    dats_dense_array_insert(&da, 40, &data2);
    dats_dense_array_insert(&da, 0, &data3);
    dats_dense_array_insert(&da, 128, &data4);

    EXPECT_TRUE(dats_dense_array_contains(&da, &data1));
    EXPECT_TRUE(dats_dense_array_contains(&da, &data2));
    EXPECT_TRUE(dats_dense_array_contains(&da, &data3));
    EXPECT_TRUE(dats_dense_array_contains(&da, &data4));

    dats_dense_array_remove(&da, 40);
    dats_dense_array_remove(&da, 0);

    EXPECT_TRUE(dats_dense_array_contains(&da, &data1));
    EXPECT_FALSE(dats_dense_array_contains(&da, &data2));
    EXPECT_FALSE(dats_dense_array_contains(&da, &data3));
    EXPECT_TRUE(dats_dense_array_contains(&da, &data4));

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_clear, ClearEmptyDenseArray)
{
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_clear(&da);

    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(sizeof(double), da.data_size);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_clear, ClearMultipleItemDenseArray)
{
    double data1 = 128.1;
    double data2 = 228.1;
    double data3 = 328.1;
    double data4 = 428.1;
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_insert(&da, 5, &data1);
    dats_dense_array_insert(&da, 40, &data2);
    dats_dense_array_insert(&da, 0, &data3);
    dats_dense_array_insert(&da, 128, &data4);

    dats_dense_array_clear(&da);

    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(sizeof(double), da.data_size);

    dats_dense_array_free(&da);
}

TEST(dats_dense_array_free, FreeEmptyDenseArray)
{
    dats_dense_array_t da = dats_dense_array_new(sizeof(double));

    dats_dense_array_free(&da);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(0, da.data_size);
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
    EXPECT_EQ(11, da.lookup_length);
    EXPECT_EQ(sizeof(double), da.data_size);

    dats_dense_array_free(&da);

    EXPECT_EQ(0, da.data_length);
    EXPECT_EQ(0, da.lookup_length);
    EXPECT_EQ(0, da.data_size);
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