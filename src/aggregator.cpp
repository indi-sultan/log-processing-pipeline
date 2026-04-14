#include "pipeline/aggregator.h"
#include <iostream>

Aggregator::Aggregator(ThreadSafeQueue<LogEntry>& input_queue)
    : input_queue_(input_queue)
{
}

void Aggregator::start()
{
    thread_ = std::thread(&Aggregator::run, this);
}

void Aggregator::join()
{
    if(thread_.joinable())
        thread_.join();
}

void Aggregator::run()
{
    start_time_ = std::chrono::steady_clock::now();

    while(true)
    {
        LogEntry entry;
        input_queue_.wait_and_pop(entry);

        // STOP signal
        if(entry.level == "__STOP__")
        {
            break;
        }

        error_count_++;
    }

    end_time_ = std::chrono::steady_clock::now();
}