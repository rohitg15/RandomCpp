#include "thread_context.h"

ThreadContext::ThreadContext()
    :
        ptr_(nullptr),
	val_(0)
{}

ThreadContext::ThreadContext(int * ptr, int val)
    :
        ptr_(ptr),
        val_(val)
{}


ThreadContext::ThreadContext(ThreadContext && other)
    :
	ptr_(other.ptr_),
	val_(other.val_)
{}


ThreadContext& ThreadContext::operator=(ThreadContext && other)
{
    if (this != &other)
    {
	ptr_ = other.ptr_;
	val_ = other.val_;
    }
    return *this;
}

void ThreadContext::operator()()
{
    *ptr_ = val_;
}

