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


template <typename T>
void ThreadSafeQueue<T>::push(T value)
{
    std::lock_guard<std::mutex> lock(mutex_);

    queue_.push(std::move(value));

    cond_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::wait_and_pop(T& value)
{
    std::unique_lock<std::mutex> lock(mutex_);

    cond_.wait(lock, [this]
    {
        return !queue_.empty();
    });

    value = std::move(queue_.front());
    queue_.pop();
}

template <typename T>
bool ThreadSafeQueue<T>::try_pop(T& value)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if(queue_.empty())
        return false;

    value = std::move(queue_.front());
    queue_.pop();

    return true;
}

template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    return queue_.empty();
}

template <typename T>
size_t ThreadSafeQueue<T>::size() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    return queue_.size();
}