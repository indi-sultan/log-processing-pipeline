#include <gtest/gtest.h>
#include <thread>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/log_entry.h"

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

// You can extract parsing logic into a function later

TEST(ParserTest, BasicParsing)
{
    std::string line = "2026-03-07 10:15:22 ERROR Database connection failed";

    std::istringstream iss(line);

    LogEntry entry;

    std::string date, time;
    iss >> date >> time;
    entry.timestamp = date + " " + time;

    iss >> entry.level;
    std::getline(iss, entry.message);

    if(!entry.message.empty() && entry.message[0] == ' ')
        entry.message.erase(0, 1);

    EXPECT_EQ(entry.timestamp, "2026-03-07 10:15:22");
    EXPECT_EQ(entry.level, "ERROR");
    EXPECT_EQ(entry.message, "Database connection failed");
}