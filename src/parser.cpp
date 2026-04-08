#include "pipeline/parser.h"
#include <sstream>

static const std::string STOP_SIGNAL = "__STOP__";

Parser::Parser(ThreadSafeQueue<std::string>& input_queue,
               ThreadSafeQueue<LogEntry>& output_queue,
               int num_threads)
    : input_queue_(input_queue),
      output_queue_(output_queue),
      num_threads_(num_threads)
{
}

void Parser::start()
{
    for(int i = 0; i < num_threads_; i++)
    {
        threads_.emplace_back(&Parser::run, this);
    }
}

void Parser::join()
{
    for(auto& t : threads_)
    {
        if(t.joinable())
            t.join();
    }
}

void Parser::run()
{
    while(true)
    {
        std::string line;
        input_queue_.wait_and_pop(line);

         // STOP condition
        if(line == STOP_SIGNAL)
        {
            break;
        }

        std::istringstream iss(line);

        LogEntry entry;

        // Parse timestamp (2 parts)
        std::string date, time;
        iss >> date >> time;
        entry.timestamp = date + " " + time;

        // Parse level
        iss >> entry.level;

        // Remaining is message
        std::getline(iss, entry.message);

        // Remove leading space from message
        if(!entry.message.empty() && entry.message[0] == ' ')
            entry.message.erase(0, 1);

        output_queue_.push(entry);
    }
}