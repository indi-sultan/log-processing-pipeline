#pragma once

#include <string>
#include <thread>
#include "thread_safe_queue.h"

class Reader
{
private:
    std::string filename_;
    ThreadSafeQueue<std::string>& queue_;
    std::thread thread_;
    int num_parser_threads_;//for stop condition in parser

    void run();

public:
    Reader(const std::string& filename,
           ThreadSafeQueue<std::string>& queue,
            int num_parser_threads);

    void start();
    void join();
};