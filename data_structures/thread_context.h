#ifndef _THREAD_CONTEXT_H_
#define _THREAD_CONTEXT_H_

class ThreadContext
{
    public:
	ThreadContext();
	ThreadContext(int *ptr, int val);

	ThreadContext(ThreadContext const&) = delete;
	ThreadContext& operator=(ThreadContext const& ) = delete;

	ThreadContext(ThreadContext && other);
	ThreadContext& operator=(ThreadContext && other);

	void operator()();

    private:
	int *ptr_;
	int val_;
};


#endif	//	_THREAD_CONTEXT_H_
