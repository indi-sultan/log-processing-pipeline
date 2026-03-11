#include <iostream>
#include <thread>
#include "pipeline/thread_safe_queue.h"

ThreadSafeQueue<int> queue;

void producer()
{
    for(int i=0;i<10;i++)
    {
        queue.push(i);
    }
}

void consumer()
{
    for(int i=0;i<10;i++)
    {
        int value;
        queue.wait_and_pop(value);

        std::cout << "Consumed: " << value << std::endl;
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}