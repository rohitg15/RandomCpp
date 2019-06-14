#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "thread_pool_queue.h"
#include <thread>

template <typename T>
class ThreadPool
{
    public:
        ThreadPool(size_t numThreads = 16);

        ThreadPool(ThreadPool const& ) = delete;
        ThreadPool& operator=(ThreadPool const& ) = delete;

        void AddJob(T const& job);
        void AddJob(T && job);
        void Join();
        void KillAllThreads();

	~ThreadPool();

    private:
	void ThreadFunc();

	std::vector<std::thread> threads_;
        ThreadPoolQueue<T> q_;
	bool killAllThreads_;
};


template <typename T>
ThreadPool<T>::ThreadPool(size_t numThreads)
    :
	killAllThreads_(false)
{
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
	threads_.emplace_back(std::thread(&ThreadPool::ThreadFunc, this));
    }
}

template <typename T>
void ThreadPool<T>::AddJob(T const& job)
{
    q_.Enqueue(job);
}

template <typename T>
void ThreadPool<T>::AddJob(T && job)
{
    q_.Enqueue(std::move(job));
}

template <typename T>
void ThreadPool<T>::Join()
{
    for (auto &thread : threads_)
    {
	if (thread.joinable())
	{
	    thread.join();
	}
    }
}

template <typename T>
void ThreadPool<T>::KillAllThreads()
{
    killAllThreads_ = true;
    q_.ReleaseThreads();
}


template <typename T>
ThreadPool<T>::~ThreadPool()
{
    KillAllThreads();
    Join();
}

template <typename T>
void ThreadPool<T>::ThreadFunc()
{
    for (;;)
    {
	T job;
	q_.Dequeue(job);
	if (killAllThreads_)
	{
	// terminate thread loop
	    break;
	}
	job();
    }
}

#endif
