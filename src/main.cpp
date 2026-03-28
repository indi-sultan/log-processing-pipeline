#include <iostream>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/reader.h"
#include "pipeline/parser.h"

int main()
{
    ThreadSafeQueue<std::string> raw_queue;
    ThreadSafeQueue<LogEntry> parsed_queue;

    Reader reader("../logs/sample.log", raw_queue);

    Parser parser(raw_queue, parsed_queue, 4);

    reader.start();
    parser.start();

    reader.join();

    // TEMP: read few parsed logs
    for(int i = 0; i < 4; i++)
    {
        LogEntry entry;
        parsed_queue.wait_and_pop(entry);

        entry.print();
    }

    return 0;
}