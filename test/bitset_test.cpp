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

TEST(dats_bitset_set, MultipleBitChanged)
{
    dats_bitset_t bt = dats_bitset_new(10);

    dats_bitset_set(&bt, 1, true);
    dats_bitset_set(&bt, 2, true);
    dats_bitset_set(&bt, 3, false);
    dats_bitset_set(&bt, 4, true);
    dats_bitset_set(&bt, 5, true);
    dats_bitset_set(&bt, 6, false);
    dats_bitset_set(&bt, 7, false);
    dats_bitset_set(&bt, 8, false);
    dats_bitset_set(&bt, 9, true);
    dats_bitset_set(&bt, 10, false);

    EXPECT_EQ(true, dats_bitset_is_set(&bt, 1));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 2));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 3));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 4));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 5));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 6));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 7));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 8));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 9));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 10));

    dats_bitset_free(&bt);
}

TEST(dats_bitset_flip, MultipleBitChanged)
{
    dats_bitset_t bt = dats_bitset_new(10);

    dats_bitset_set(&bt, 1, true);
    dats_bitset_set(&bt, 2, true);
    dats_bitset_set(&bt, 4, true);
    dats_bitset_set(&bt, 5, true);
    dats_bitset_set(&bt, 9, true);

    dats_bitset_flip(&bt);

    EXPECT_EQ(false, dats_bitset_is_set(&bt, 1));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 2));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 3));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 4));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 5));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 6));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 7));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 8));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 9));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 10));

    dats_bitset_free(&bt);
}

TEST(dats_bitset_is_set, ManipulatedBitset)
{
    dats_bitset_t bt = dats_bitset_new(33);

    EXPECT_EQ(false, dats_bitset_is_set(&bt, 1));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 9));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 33));

    dats_bitset_set(&bt, 1, true);
    dats_bitset_set(&bt, 9, true);
    dats_bitset_set(&bt, 33, true);

    EXPECT_EQ(true, dats_bitset_is_set(&bt, 1));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 9));
    EXPECT_EQ(true, dats_bitset_is_set(&bt, 33));

    dats_bitset_set(&bt, 33, false);

    EXPECT_EQ(false, dats_bitset_is_set(&bt, 33));

    dats_bitset_free(&bt);
}

TEST(dats_bitset_reset, ResetAllSetBit)
{
    dats_bitset_t bt = dats_bitset_new(10);

    dats_bitset_set(&bt, 1, true);
    dats_bitset_set(&bt, 2, true);
    dats_bitset_set(&bt, 4, true);
    dats_bitset_set(&bt, 5, true);
    dats_bitset_set(&bt, 9, true);

    dats_bitset_reset(&bt);

    EXPECT_EQ(false, dats_bitset_is_set(&bt, 1));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 2));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 3));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 4));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 5));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 6));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 7));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 8));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 9));
    EXPECT_EQ(false, dats_bitset_is_set(&bt, 10));

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