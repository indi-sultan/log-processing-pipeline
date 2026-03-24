#include <iostream>
<<<<<<< HEAD

int main()
{
    std::cout << "setup of project is completed\n";
=======
#include "pipeline/log_entry.h"

int main()
{
    LogEntry log;

    log.timestamp = "2026-03-07 10:15:22";
    log.level = "ERROR";
    log.message = "Database connection failed";

    log.print();
    
>>>>>>> feature/thread-safe-queue
    return 0;
}