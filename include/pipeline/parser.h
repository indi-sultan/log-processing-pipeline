#pragma once

#include <thread>
#include <vector>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/log_entry.h"

class Parser
{
private:
    ThreadSafeQueue<std::string>& input_queue_;
    ThreadSafeQueue<LogEntry>& output_queue_;

    std::vector<std::thread> threads_;
    int num_threads_;

    void run();

public:
    Parser(ThreadSafeQueue<std::string>& input_queue,
           ThreadSafeQueue<LogEntry>& output_queue,
           int num_threads);

    void start();
    void join();
};