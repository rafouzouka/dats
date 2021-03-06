#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

extern "C"
{
    #include <dats/dats.h>

    typedef struct
    {
        uint64_t x;
        uint64_t y;
    } _Fake_Position;
}

TEST(dats_stack_new, CreateAnEmptyStack)
{
    dats_stack_t s = dats_stack_new(sizeof(_Fake_Position));

    EXPECT_EQ(s.ll.data_size, sizeof(_Fake_Position));
    EXPECT_EQ(s.ll.head, nullptr);
    EXPECT_EQ(s.ll.tail, nullptr);
    EXPECT_EQ(s.ll.length, 0);

    dats_stack_free(&s);
}

TEST(dats_stack_push, PushToAnEmptyStack)
{
    _Fake_Position data1 = { 11, 22 };   
    dats_stack_t s = dats_stack_new(sizeof(_Fake_Position));
    EXPECT_EQ(0, s.ll.length);

    dats_stack_push(&s, &data1);
    EXPECT_EQ(1, s.ll.length);

    const _Fake_Position *pos = (const _Fake_Position*)dats_stack_get(&s, 0);
    EXPECT_EQ(pos->x, data1.x);
    EXPECT_EQ(pos->y, data1.y);

    dats_stack_free(&s);
}

TEST(dats_stack_push, PushToTwoItemStack)
{
    _Fake_Position data1 = { 11, 22 };   
    _Fake_Position data2 = { 44, 88 };   
    dats_stack_t s = dats_stack_new(sizeof(_Fake_Position));
    EXPECT_EQ(0, s.ll.length);

    dats_stack_push(&s, &data1);
    dats_stack_push(&s, &data2);
    EXPECT_EQ(2, s.ll.length);

    const _Fake_Position *pos = (const _Fake_Position*)dats_stack_get(&s, 0);
    EXPECT_EQ(pos->x, data2.x);
    EXPECT_EQ(pos->y, data2.y);

    const _Fake_Position *pos2 = (const _Fake_Position*)dats_stack_get(&s, 1);
    EXPECT_EQ(pos2->x, data1.x);
    EXPECT_EQ(pos2->y, data1.y);

    dats_stack_free(&s);
}

TEST(dats_stack_pop, MultiplePopInThreeItemsStack)
{
    _Fake_Position data1 = { 11, 22 };
    _Fake_Position data2 = { 444, 888 };
    _Fake_Position data3 = { 99, 999 };

    dats_stack_t s = dats_stack_new(sizeof(_Fake_Position));
    dats_stack_push(&s, &data1);
    dats_stack_push(&s, &data2);
    dats_stack_push(&s, &data3);

    _Fake_Position *res = (_Fake_Position *)dats_stack_pop(&s);
    EXPECT_EQ(res->x, data3.x);
    EXPECT_EQ(res->y, data3.y);
    free(res);

    _Fake_Position *res2 = (_Fake_Position *)dats_stack_pop(&s);
    EXPECT_EQ(res2->x, data2.x);
    EXPECT_EQ(res2->y, data2.y);
    free(res2);

    _Fake_Position *res3 = (_Fake_Position *)dats_stack_pop(&s);
    EXPECT_EQ(res3->x, data1.x);
    EXPECT_EQ(res3->y, data1.y);
    free(res3);

    dats_stack_free(&s);
}

TEST(dats_stack_peek, PeekOneItemStack)
{
    _Fake_Position data1 = { 111, 222 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data1);

    const _Fake_Position *pos =  (const _Fake_Position *)dats_stack_peek(&q);

    EXPECT_EQ(q.ll.length, 1);
    EXPECT_EQ(pos->x, data1.x);
    EXPECT_EQ(pos->y, data1.y);

    dats_stack_free(&q);
}

TEST(dats_stack_peek, PeekTwoItemStack)
{
    _Fake_Position data1 = { 111, 222 };
    _Fake_Position data2 = { 444, 666 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data1);
    dats_stack_push(&q, &data2);

    const _Fake_Position *pos1 =  (const _Fake_Position *)dats_stack_peek(&q);
    EXPECT_EQ(pos1->x, data2.x);
    EXPECT_EQ(pos1->y, data2.y);

    const _Fake_Position *pos2 =  (const _Fake_Position *)dats_stack_peek(&q);
    EXPECT_EQ(pos2->x, data2.x);
    EXPECT_EQ(pos2->y, data2.y);

    void *ptr = dats_stack_pop(&q);
    free(ptr);

    const _Fake_Position *pos3 =  (const _Fake_Position *)dats_stack_peek(&q);
    EXPECT_EQ(pos3->x, data1.x);
    EXPECT_EQ(pos3->y, data1.y);

    dats_stack_free(&q);
}

TEST(dats_stack_get, GetOneItemStack)
{
    _Fake_Position data1 = { 11, 22 };   

    dats_stack_t s = dats_stack_new(sizeof(_Fake_Position));
    dats_stack_push(&s, &data1);

    const _Fake_Position *pos = (const _Fake_Position*)dats_stack_get(&s, 0);
    EXPECT_EQ(pos->x, data1.x);
    EXPECT_EQ(pos->y, data1.y);

    dats_stack_free(&s);
}

TEST(dats_stack_contains, EmptyStack)
{
    _Fake_Position data = { 111, 222 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    EXPECT_EQ(dats_stack_contains(&q, &data), false);

    dats_stack_free(&q);
}

TEST(dats_stack_contains, DoesNotContain)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };

    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));
    dats_stack_push(&q, &data);

    EXPECT_EQ(dats_stack_contains(&q, &data2), false);

    dats_stack_free(&q);
}

TEST(dats_stack_contains, ManagedStackAndContain)
{
    _Fake_Position data = { 333, 222 };
    _Fake_Position data2 = { 333, 444 };
    _Fake_Position data3 = { 333, 888 };

    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data);
    dats_stack_push(&q, &data2);
    dats_stack_push(&q, &data3);

    EXPECT_EQ(dats_stack_contains(&q, &data), true);

    void *ptr = dats_stack_pop(&q);
    free(ptr);

    EXPECT_EQ(dats_stack_contains(&q, &data3), false);

    dats_stack_free(&q);
}

TEST(dats_stack_length, EmptyStack)
{
    dats_stack_t q = dats_stack_new(sizeof(double));

    EXPECT_EQ(0, dats_stack_length(&q));

    dats_stack_free(&q);
}

TEST(dats_stack_length, Manipulatedstack)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 333, 444 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    EXPECT_EQ(0, dats_stack_length(&q));

    dats_stack_push(&q, &data);
    dats_stack_push(&q, &data2);

    EXPECT_EQ(2, dats_stack_length(&q));

    void *ptr = dats_stack_pop(&q);
    free(ptr);

    EXPECT_EQ(1, dats_stack_length(&q));

    dats_stack_free(&q);
}

TEST(dats_stack_clear, ClearingOneItemStack)
{
    _Fake_Position data = { 111, 222 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data);

    dats_stack_clear(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));

    dats_stack_push(&q, &data);

    EXPECT_NE(q.ll.head, nullptr);
    EXPECT_NE(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 1);

    dats_stack_free(&q);
}

TEST(dats_stack_clear, ClearingMultipleItemStack)
{
    _Fake_Position data = { 111, 222 };
    _Fake_Position data2 = { 222, 333 };
    _Fake_Position data3 = { 333, 222 };
    _Fake_Position data4 = { 444, 222 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data);
    dats_stack_push(&q, &data2);
    dats_stack_push(&q, &data3);
    dats_stack_push(&q, &data4);

    dats_stack_clear(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));

    dats_stack_push(&q, &data2);
    dats_stack_push(&q, &data4);

    const _Fake_Position *pos2 = (const _Fake_Position*)dats_stack_get(&q, 1);
    const _Fake_Position *pos4 = (const _Fake_Position*)dats_stack_get(&q, 0);
    EXPECT_EQ(pos2->x, data2.x);
    EXPECT_EQ(pos4->x, data4.x);

    EXPECT_NE(q.ll.head, nullptr);
    EXPECT_NE(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 2);

    dats_stack_free(&q);
}

TEST(dats_stack_free, FreeingEmptyStack)
{
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_free(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
}

TEST(dats_stack_free, FreeingAOneItemStack)
{
    _Fake_Position data = { 111, 222 };
    dats_stack_t q = dats_stack_new(sizeof(_Fake_Position));

    dats_stack_push(&q, &data);

    dats_stack_free(&q);

    EXPECT_EQ(q.ll.head, nullptr);
    EXPECT_EQ(q.ll.tail, nullptr);
    EXPECT_EQ(q.ll.length, 0);
    EXPECT_EQ(q.ll.data_size, sizeof(_Fake_Position));
}
