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

// TEST(dats_queue_new, CreateAnEmptyQueue)
// {
//     dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

//     EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
//     EXPECT_EQ(q.ll.head, nullptr);
//     EXPECT_EQ(q.ll.tail, nullptr);
//     EXPECT_EQ(q.ll.length, 0);

//     dats_queue_free(&q);
// }
