#include "pipeline/aggregator.h"
#include <iostream>

Aggregator::Aggregator(ThreadSafeQueue<LogEntry>& input_queue)
    : input_queue_(input_queue)
{
}

int Aggregator::getErrorCount() const
{
    return error_count_.load();
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

void Aggregator::printStats()
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time_ - start_time_
    ).count();

    double seconds = duration / 1000.0;

    double throughput = (seconds > 0) ? error_count_ / seconds : 0;

    std::cout << "\n===== Aggregator Stats =====\n";
    std::cout << "Total ERROR logs: " << error_count_ << std::endl;
    std::cout << "Processing time: " << seconds << " seconds\n";
    std::cout << "Throughput: " << throughput << " logs/sec\n";
}