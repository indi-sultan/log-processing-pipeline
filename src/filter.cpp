#include "pipeline/filter.h"

bool shouldPass(const LogEntry& entry) //helper function
{
    return entry.level == "ERROR";
}

void Filter::start()
{
    thread_ = std::thread(&Filter::run, this);
}

void Filter::join()
{
    if(thread_.joinable())
        thread_.join();
}

Filter::Filter(ThreadSafeQueue<LogEntry>& input_queue,
               ThreadSafeQueue<LogEntry>& output_queue)
    : input_queue_(input_queue),
      output_queue_(output_queue)
{
}

void Filter::run()
{
    while(true)
    {
        LogEntry entry;
        input_queue_.wait_and_pop(entry);

        //STOP condition
        if(entry.level == "__STOP__")
        {
            output_queue_.push(entry);  // forward STOP
            break;
        }

        if (shouldPass(entry))
        {
            output_queue_.push(entry);
        }
        //Filtering logic
        // if(entry.level == "ERROR")
        // {
        //     output_queue_.push(entry);
        // }
    }
}