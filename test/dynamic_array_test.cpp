#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

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

TEST(dats_dynamic_array_free, FreeEmptyDynamicArray)
{
    dats_dynamic_array_t da = dats_dynamic_array_new(4, sizeof(int));

    dats_dynamic_array_free(&da);

    EXPECT_EQ(da.capacity, 0);
    EXPECT_EQ(da.length, 0);
    EXPECT_EQ(da.buffer, nullptr);
    EXPECT_EQ(da.data_size, sizeof(int));
}