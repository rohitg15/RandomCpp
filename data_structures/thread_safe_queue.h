#ifndef _THREAD_SAFE_QUEUE_H_
#define _THREAD_SAFE_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
    public:
        ThreadSafeQueue();

        ThreadSafeQueue(ThreadSafeQueue const&) = delete;
        ThreadSafeQueue& operator=(ThreadSafeQueue const&) = delete;

        void Enqueue(T const& item);
        void Enqueue(T && item);
        void Dequeue(T & item);
        size_t Size() const;
        bool IsEmpty() const;

    private:
        std::queue<T> q_;
        mutable std::mutex qMtx_;
        std::condition_variable qCnd_;        
};


template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{}

template <typename T>
void ThreadSafeQueue<T>::Enqueue(T const& item)
{
    {
        std::lock_guard<std::mutex> lock{qMtx_};
        q_.emplace(item);
    }
    qCnd_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::Enqueue(T && item)
{
    {
        std::lock_guard<std::mutex> lock{qMtx_};
        q_.emplace(std::move(item));
    }
    qCnd_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::Dequeue(T & item)
{
    std::unique_lock<std::mutex> lock(qMtx_);
    qCnd_.wait(lock, [this]{
        return !q_.empty();
    });
    item = q_.front();
    q_.pop();
}

template <typename T>
size_t ThreadSafeQueue<T>::Size() const
{
    std::lock_guard<std::mutex> lock{qMtx_};
    return q_.size();
}

template <typename T>
bool ThreadSafeQueue<T>::IsEmpty() const
{
    std::lock_guard<std::mutex> lock{qMtx_};
    return q_.empty();
}
#endif  //  _THREAD_SAFE_QUEUE_H_