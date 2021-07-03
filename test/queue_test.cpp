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

TEST(dats_queue_dequeue, DequeueEmptyQueue)
{
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    EXPECT_DEATH(dats_queue_dequeue(&q), "Assertion");

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

    EXPECT_DEATH(dats_queue_dequeue(&q), "Assertion");

    free(pos1);
    free(pos2);
    dats_queue_free(&q);
}

TEST(dats_queue_get, GetAnEmptyQueue)
{
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    EXPECT_DEATH(dats_queue_get(&q, 0), "Assertion");

    dats_queue_free(&q);
}

TEST(dats_queue_get, GetIndexOutOfRange)
{
    _Fake_Position data = { 111, 222 };
    dats_queue_t q = dats_queue_new(sizeof(_Fake_Position));

    dats_queue_enqueue(&q, &data);

    EXPECT_DEATH(dats_queue_get(&q, 1), "Assertion");

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