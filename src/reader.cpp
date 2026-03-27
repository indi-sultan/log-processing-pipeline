#include "pipeline/reader.h"
#include <fstream>
#include <iostream>

Reader::Reader(const std::string& filename,
               ThreadSafeQueue<std::string>& queue)
    : filename_(filename), queue_(queue)
{
}

void Reader::start()
{
    thread_ = std::thread(&Reader::run, this);
}

void Reader::join()
{
    if(thread_.joinable())
        thread_.join();
}

void Reader::run()
{
    std::ifstream file(filename_);

    if(!file.is_open())
    {
        std::cerr << "Failed to open log file\n";
        return;
    }

    std::string line;

    while(std::getline(file, line))
    {
        queue_.push(line);
    }
}