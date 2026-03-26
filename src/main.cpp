#include <iostream>
#include "pipeline/log_entry.h"

int main()
{
    LogEntry log;

    log.timestamp = "2026-03-07 10:15:22";
    log.level = "ERROR";
    log.message = "Database connection failed";

    log.print();
    
    return 0;
}