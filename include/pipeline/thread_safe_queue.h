#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;

public:
    ThreadSafeQueue() = default;

    void push(T value);
    bool try_pop(T& value);
    void wait_and_pop(T& value);

    bool empty() const;
    size_t size() const;
};