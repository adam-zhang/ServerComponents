#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int count)
	: threadCount_(count)
	  , isRunning_(false)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::start()
{
	isRunning_ = true;
	for(int i = 0; i != threadCount_; ++i)
		threads_.emplace_back(std::thread(&ThreadPool::work, this));
}

void ThreadPool::work()
{
	while(isRunning_)
	{
		Task task;
		std::unique_lock<std::mutex> lock(mutex_);
		if (!tasks_.empty())
		{
			task = tasks_.front();
			tasks_.pop();
		}
		else if(isRunning_ && tasks_.empty())
			condition_.wait(lock);
		if (task)
			task();
	}
}	

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock;
		isRunning_ = false;
		condition_.notify_all();
	}
	for(std::thread& t : threads_)
		if (t.joinable())
			t.join();
}

void ThreadPool::append(const Task& task)
{
	if (isRunning_)
	{
		std::unique_lock<std::mutex> lock;
		tasks_.push(task);
		condition_.notify_one();
	}
}

