#include <gtest/gtest.h>
#include "pipeline/thread_safe_queue.h"

TEST(ThreadSafeQueueTest, PushPop)
{
    ThreadSafeQueue<int> queue;

    queue.push(1);
    queue.push(2);

    int value;

    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 1);

    EXPECT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, 2);
}