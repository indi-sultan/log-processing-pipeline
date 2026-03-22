#include "pipeline/parser.h"
#include <sstream>

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
        threads_.emplace_back(&Parser::run, this);//will add parser run function
    }
}