#include <iostream>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/reader.h"
#include "pipeline/parser.h"

int main()
{
    ThreadSafeQueue<std::string> raw_queue;
    ThreadSafeQueue<LogEntry> parsed_queue;

    int parser_threads = 4;

    Reader reader("../logs/sample.log", raw_queue, parser_threads);

    Parser parser(raw_queue, parsed_queue, parser_threads);

    reader.start();
    parser.start();

    reader.join();
    parser.join();

    // Read all parsed logs
    while(!parsed_queue.empty())
    {
        LogEntry entry;
        parsed_queue.try_pop(entry);
        entry.print();
    }
    return 0;
}