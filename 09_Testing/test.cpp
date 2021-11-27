#include <gtest/gtest.h>

#include "buf.h"

TEST(SimpleBufTest, InitializationTest) {
    float *a = 0;
    ASSERT_EQ(buf_capacity(a), 0);
    ASSERT_EQ(buf_size(a), 0);
    // Push to buffer
    buf_push(a, 1.3f);
    ASSERT_EQ(buf_size(a), 1);
    ASSERT_EQ(a[0], (float)1.3f);
    // Clear buffer
    buf_clear(a);
    ASSERT_EQ(buf_size(a), 0);
    ASSERT_NE(a, nullptr);
    // Free buffer
    buf_free(a);
    ASSERT_EQ(a, nullptr);
}

TEST(SimpleBufTest, NullPointerClearingTest) {
    float *a = nullptr;
    buf_clear(a);
    ASSERT_EQ(buf_size(a), 0);
    ASSERT_EQ(a, nullptr);
}

TEST(PushPopBufTest, LoopPushTest) {
    long *ai = nullptr;
    for (int i = 0; i < 10000; i++) {
        buf_push(ai, i);
    }
    ASSERT_EQ(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ASSERT_EQ(match, 10000);
    buf_free(ai);
    ASSERT_EQ(ai, nullptr);
}

TEST(PushPopBufTest, GrowTruncTest) {
    long *ai = 0;
    buf_grow(ai, 1000);
    ASSERT_EQ(buf_capacity(ai), 1000);
    ASSERT_EQ(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ASSERT_EQ(buf_capacity(ai), 100);
    buf_free(ai);
    ASSERT_EQ(ai, nullptr);
}

TEST(PushPopBufTest, PushTruncTest) {
    float *a = nullptr;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ASSERT_EQ(buf_size(a), 4);
    ASSERT_EQ(buf_pop(a), (float)1.4f);
    buf_trunc(a, 3);
    ASSERT_EQ(buf_size(a), 3);
    ASSERT_EQ(buf_pop(a), (float)1.3f);
    ASSERT_EQ(buf_pop(a), (float)1.2f);
    ASSERT_EQ(buf_pop(a), (float)1.1f);
    ASSERT_EQ(buf_size(a), 0);
    buf_free(a);
    ASSERT_EQ(a, nullptr);
}

