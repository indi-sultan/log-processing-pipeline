#include <iostream>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/reader.h"
#include "pipeline/parser.h"
#include "pipeline/filter.h"

int main()
{
    ThreadSafeQueue<std::string> raw_queue;
    ThreadSafeQueue<LogEntry> parsed_queue;
    ThreadSafeQueue<LogEntry> error_queue;

    int parser_threads = 4;

    Reader reader("../logs/sample.log", raw_queue, parser_threads);

    Parser parser(raw_queue, parsed_queue, parser_threads);

    Filter filter(parsed_queue, error_queue);

    reader.start();
    parser.start();
    filter.start();

    reader.join();
    parser.join();
    filter.join();

    // // Read all parsed logs
    // while(!parsed_queue.empty())
    // {
    //     LogEntry entry;
    //     parsed_queue.try_pop(entry);
    //     entry.print();
    // }

    //output filtered logs
    while (!error_queue.empty())
    {
        LogEntry entry;
        error_queue.try_pop(entry);

        if(entry.level != "__STOP__") //ignore stop signal
            entry.print();
    }
    


    return 0;
}