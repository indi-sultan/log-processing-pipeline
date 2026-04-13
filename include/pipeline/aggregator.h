#pragma once

#include <thread>
#include <atomic>
#include <chrono>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/log_entry.h"

class Aggregator
{
private:
    ThreadSafeQueue<LogEntry>& input_queue_;
    std::thread thread_;

    std::atomic<int> error_count_{0};

    std::chrono::steady_clock::time_point start_time_;
    std::chrono::steady_clock::time_point end_time_;

    void run();

public:
    Aggregator(ThreadSafeQueue<LogEntry>& input_queue);

    void start();
    void join();

    void printStats();
};