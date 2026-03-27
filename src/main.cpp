#include <iostream>
#include "pipeline/thread_safe_queue.h"
#include "pipeline/reader.h"

int main()
{
    ThreadSafeQueue<std::string> queue;

    Reader reader("../logs/sample.log", queue);

    reader.start();
    reader.join();

    while(!queue.empty())
    {
        std::string line;
        queue.try_pop(line);

        std::cout << line << std::endl;
    }

    return 0;
}