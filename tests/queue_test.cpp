#include <gtest/gtest.h>
#include <thread>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/log_entry.h"
#include "pipeline/filter.h"

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

TEST(FilterTest, PassErrorLogs)
{
    LogEntry entry;
    entry.level = "ERROR";

    EXPECT_TRUE(shouldPass(entry));
}

TEST(FilterTest, RejectInfoLogs)
{
    LogEntry entry;
    entry.level = "INFO";

    EXPECT_FALSE(shouldPass(entry));
}

TEST(FilterTest, RejectWarningLogs)
{
    LogEntry entry;
    entry.level = "WARNING";

    EXPECT_FALSE(shouldPass(entry));
}

TEST(FilterTest, StopSignal)
{
    LogEntry entry;
    entry.level = "__STOP__";

    // STOP should NOT be treated as normal log
    EXPECT_FALSE(shouldPass(entry));
}

TEST(FilterIntegrationTest, FiltersCorrectly)
{
    ThreadSafeQueue<LogEntry> input_queue;
    ThreadSafeQueue<LogEntry> output_queue;

    Filter filter(input_queue, output_queue);

    filter.start();

    // Push test data
    LogEntry e1{"", "INFO", "msg"};
    LogEntry e2{"", "ERROR", "error msg"};
    LogEntry stop{"", "__STOP__", ""};

    input_queue.push(e1);
    input_queue.push(e2);
    input_queue.push(stop);

    filter.join();

    LogEntry result;
    output_queue.wait_and_pop(result);

    EXPECT_EQ(result.level, "ERROR");
}