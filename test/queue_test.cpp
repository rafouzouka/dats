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

TEST(dats_queue_new, CreateAnEmptyQueue)
{
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);

    dats_queue_free(&q);
}

TEST(dats_queue_enqueue, EnqueueEmptyQueue)
{
    _Fake_Position data = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);

    const _Fake_Position *pos1 = (const _Fake_Position*)dats_queue_get(&q, 0);

    EXPECT_EQ(pos1->x, data.x);
    EXPECT_EQ(pos1->y, data.y);

    EXPECT_EQ(q.ll.length, 1);
    EXPECT_EQ(q.ll.head, q.ll.tail);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(((_Fake_Position*)q.ll.head->data)->x, data.x);
    EXPECT_EQ(((_Fake_Position*)q.ll.head->data)->y, data.y);

    dats_queue_free(&q);
}

TEST(dats_queue_enqueue, EnqueueAlreadyOneItemQueue)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);
    dats_queue_enqueue(&q, &data2);

    const _Fake_Position *pos1 = (const _Fake_Position*)dats_queue_get(&q, 0);
    const _Fake_Position *pos2 = (const _Fake_Position*)dats_queue_get(&q, 1);

    EXPECT_EQ(pos1->x, data2.x);
    EXPECT_EQ(pos1->y, data2.y);

    EXPECT_EQ(pos2->x, data.x);
    EXPECT_EQ(pos2->y, data.y);

    EXPECT_EQ(q.ll.length, 2);
    EXPECT_NE(q.ll.head, q.ll.tail);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));

    EXPECT_EQ(((_Fake_Position*)q.ll.head->data)->x, data2.x);
    EXPECT_EQ(((_Fake_Position*)q.ll.head->data)->y, data2.y);

    EXPECT_EQ(((_Fake_Position*)q.ll.tail->data)->x, data.x);
    EXPECT_EQ(((_Fake_Position*)q.ll.tail->data)->y, data.y);

    dats_queue_free(&q);
}

TEST(dats_queue_dequeue, DequeueTwoItemQueue)
{
    _Fake_Position data1 = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data1);
    dats_queue_enqueue(&q, &data2);

    _Fake_Position *pos1 = (_Fake_Position*)dats_queue_dequeue(&q);
    EXPECT_EQ(data1.x, pos1->x);
    EXPECT_EQ(data1.y, pos1->y);

    _Fake_Position *pos2 = (_Fake_Position*)dats_queue_dequeue(&q);
    EXPECT_EQ(data2.x, pos2->x);
    EXPECT_EQ(data2.y, pos2->y);

    free(pos1);
    free(pos2);
    dats_queue_free(&q);
}

TEST(dats_queue_peek, PeekOneItemQueue)
{
    _Fake_Position data1 = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data1);

    const _Fake_Position *pos =  (const _Fake_Position *)dats_queue_peek(&q);

    EXPECT_EQ(pos->x, data1.x);
    EXPECT_EQ(pos->y, data1.y);

    dats_queue_free(&q);
}

TEST(dats_queue_peek, PeekTwoItemQueue)
{
    _Fake_Position data1 = { 111, 222 };
    _Fake_Position data2 = { 444, 666 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data1);
    dats_queue_enqueue(&q, &data2);

    const _Fake_Position *pos1 =  (const _Fake_Position *)dats_queue_peek(&q);
    EXPECT_EQ(pos1->x, data1.x);
    EXPECT_EQ(pos1->y, data1.y);

    const _Fake_Position *pos2 =  (const _Fake_Position *)dats_queue_peek(&q);
    EXPECT_EQ(pos2->x, data1.x);
    EXPECT_EQ(pos2->y, data1.y);

    void *ptr = dats_queue_dequeue(&q);
    free(ptr);

    const _Fake_Position *pos3 =  (const _Fake_Position *)dats_queue_peek(&q);
    EXPECT_EQ(pos3->x, data2.x);
    EXPECT_EQ(pos3->y, data2.y);

    dats_queue_free(&q);
}

TEST(dats_queue_get, GetTwoItemFromQueue)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);
    dats_queue_enqueue(&q, &data2);

    const _Fake_Position *pos1 = (const _Fake_Position*)dats_queue_get(&q, 0);
    const _Fake_Position *pos2 = (const _Fake_Position*)dats_queue_get(&q, 1);

    EXPECT_EQ(pos1->x, data2.x);
    EXPECT_EQ(pos1->y, data2.y);

    EXPECT_EQ(pos2->x, data.x);
    EXPECT_EQ(pos2->y, data.y);

    dats_queue_free(&q);
}

static void _test_MapOneItemQueue(const void* d)
{
    const _Fake_Position *data = (const _Fake_Position *)d;
    EXPECT_EQ(data->x, 111);
    EXPECT_EQ(data->y, 222);
}

TEST(dats_queue_map, MapOneItemQueue)
{
    _Fake_Position data = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);

    dats_queue_map(&q, _test_MapOneItemQueue);

    dats_queue_free(&q);
}

TEST(dats_queue_contains, EmptyQueue)
{
    _Fake_Position data = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    EXPECT_EQ(dats_queue_contains(&q, &data), false);

    dats_queue_free(&q);
}

TEST(dats_queue_contains, DoesNotContain)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));
    dats_queue_enqueue(&q, &data);

    EXPECT_EQ(dats_queue_contains(&q, &data2), false);

    dats_queue_free(&q);
}

TEST(dats_queue_contains, ManagedQueueAndContain)
{
    _Fake_Position data = { 333, 222 };
    _Fake_Position data2 = { 333, 444 };
    _Fake_Position data3 = { 333, 888 };

    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);
    dats_queue_enqueue(&q, &data2);
    dats_queue_enqueue(&q, &data3);

    EXPECT_EQ(dats_queue_contains(&q, &data), true);

    void *ptr = dats_queue_dequeue(&q);
    free(ptr);

    EXPECT_EQ(dats_queue_contains(&q, &data), false);

    dats_queue_free(&q);
}

TEST(dats_queue_length, EmptyQueue)
{
    dats_queue_t q = dats_queue_new(sizeof(double));

    EXPECT_EQ(0, dats_queue_length(&q));

    dats_queue_free(&q);
}

TEST(dats_queue_length, ManipulatedQueue)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    EXPECT_EQ(0, dats_queue_length(&q));

    dats_queue_enqueue(&q, &data);
    dats_queue_enqueue(&q, &data2);

    EXPECT_EQ(2, dats_queue_length(&q));

    void *ptr = dats_queue_dequeue(&q);
    free(ptr);

    EXPECT_EQ(1, dats_queue_length(&q));

    dats_queue_free(&q);
}

TEST(dats_queue_free, FreeingAnEmptyQueue)
{
    dats_queue_t q = dats_queue_new(sizeof(double));

    dats_queue_free(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(double));
}

TEST(dats_queue_free, FreeingAOneItemQueue)
{
    _Fake_Position data = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);

    dats_queue_free(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
}
