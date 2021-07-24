#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

extern "C"
{
    #include <dats/dats.h>
}

TEST(dats_bitset_new, CreateSimpleBitSet)
{
    dats_bitset_t bt = dats_bitset_new(10);

    EXPECT_NE(bt.buffer, nullptr);
    EXPECT_EQ(bt.bytes_needed, 2);
    EXPECT_EQ(bt.size, 10);

    dats_bitset_free(&bt);
}

TEST(dats_bitset_new, CreateBigBitSet)
{
    dats_bitset_t bt = dats_bitset_new(300);

    EXPECT_NE(bt.buffer, nullptr);
    EXPECT_EQ(bt.bytes_needed, (300 / 8) + 1);
    EXPECT_EQ(bt.size, 300);

    dats_bitset_free(&bt);
}

TEST(dats_bitset_free, FreeingSimpleBitset)
{
    dats_bitset_t bt = dats_bitset_new(17);

    dats_bitset_free(&bt);

    EXPECT_EQ(bt.buffer, nullptr);
    EXPECT_EQ(bt.bytes_needed, 0);
    EXPECT_EQ(bt.size, 0);
}