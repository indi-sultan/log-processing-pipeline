#include "pipeline/reader.h"
#include <fstream>
#include <iostream>

Reader::Reader(const std::string& filename,
               ThreadSafeQueue<std::string>& queue,
                int num_parser_threads)
    : filename_(filename), queue_(queue), num_parser_threads_(num_parser_threads)
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

    //Send STOP signals
    for(int i = 0; i < num_parser_threads_; i++)
    {
        queue_.push("__STOP__");
    }
}