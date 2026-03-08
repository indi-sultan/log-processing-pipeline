#pragma once

#include <iostream>
#include <string>


struct LogEntry
{
    std::string timestamp;
    std::string level;
    std::string message;

    void print() const
    {
        std::cout << "TIMESTAMP: " << timestamp << std::endl;
        std::cout << "LEVEL: " << level << std::endl;
        std::cout << "MESSAGE: " << message << std::endl;
    }
};