#pragma once

#include <thread>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/log_entry.h"

class Filter
{
private:
    ThreadSafeQueue<LogEntry>& input_queue_;
    ThreadSafeQueue<LogEntry>& output_queue_;

    std::thread thread_;

    void run();

public:
    Filter(ThreadSafeQueue<LogEntry>& input_queue,
           ThreadSafeQueue<LogEntry>& output_queue);

    void start();
    void join();
};