#ifndef _THREAD_POOL_QUEUE_H_
#define _THREAD_POOL_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadPoolQueue
{
    public:
        ThreadPoolQueue();

        ThreadPoolQueue(ThreadPoolQueue const&) = delete;
        ThreadPoolQueue& operator=(ThreadPoolQueue const& ) = delete;

       
        void Enqueue(T const& item);
        void Enqueue(T && item);
        void Dequeue(T & item);
        void ReleaseThreads();
        size_t Size() const;
        bool IsEmpty() const;

    private:
        std::queue<T> q_;
        mutable std::mutex qMtx_;
        std::condition_variable qCnd_;
        bool releaseThreads_;  
};

template <typename T>
ThreadPoolQueue<T>::ThreadPoolQueue()
    :
        releaseThreads_(false)
{}

template <typename T>
void ThreadPoolQueue<T>::Enqueue(T const& item)
{
    {
        std::lock_guard<std::mutex> lock{qMtx_};
        q_.emplace(item);
    }
    qCnd_.notify_one();
}

template <typename T>
void ThreadPoolQueue<T>::Enqueue(T && item)
{
    {
        std::lock_guard<std::mutex> lock{qMtx_};
        q_.emplace(std::move(item));
    }
    qCnd_.notify_one();
}

template <typename T>
void ThreadPoolQueue<T>::Dequeue(T & item)
{
    std::unique_lock<std::mutex> lock(qMtx_);
    qCnd_.wait(lock, [this]{
        return !q_.empty() || releaseThreads_;
    });

    if (releaseThreads_)
    {
        return;
    }

    item = std::move(q_.front());
    q_.pop();
}

template <typename T>
void ThreadPoolQueue<T>::ReleaseThreads()
{
    {
	std::lock_guard<std::mutex> lock{qMtx_};
        releaseThreads_ = true;
    }
    qCnd_.notify_all();
}

template <typename T>
size_t ThreadPoolQueue<T>::Size() const
{
    std::lock_guard<std::mutex> lock{qMtx_};
    return q_.size();
}

template <typename T>
bool ThreadPoolQueue<T>::IsEmpty() const
{
    std::lock_guard<std::mutex> lock{qMtx_};
    return q_.empty();
}

#endif  //  _THREAD_POOL_QUEUE_H_
