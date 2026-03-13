#include <gtest/gtest.h>
#include <thread>
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

TEST(ThreadSafeQueueTest, ProducerConsumer)
{
    ThreadSafeQueue<int> queue;

    std::thread producer(
        [&]()
        {
            for (int i = 0; i < 100; i++)
            {
                queue.push(i);
            }
            
        }
    );
    int count = 0;
    std::thread consumer([&]()
    {
        for (int i = 0; i < 100; i++)
        {
            int value;
            queue.wait_and_pop(value);
            count++;
        }
        
    }
    );

    producer.join();
    consumer.join();
    EXPECT_EQ(count, 100);
}