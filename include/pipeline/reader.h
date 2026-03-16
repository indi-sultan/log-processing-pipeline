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

    void run();

public:
    Reader(const std::string& filename,
           ThreadSafeQueue<std::string>& queue);

    void start();
    void join();
};