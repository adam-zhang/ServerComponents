#ifndef __QUEUE__H
#define __QUEUE__H 

#include <queue>
#include <mutex>
#include <condition_variable>
#include <initializer_list>
#include <iostream>

template<typename T>
class Queue
{
	private:
		std::mutex mutex_;
		std::condition_variable condition_;
		std::queue<T> data_;
	public:
		Queue()=default;
		Queue(const Queue&)=delete;
		Queue& operator=(const Queue&)=delete;

		void push(const T& value)
		{
			std::lock_guard<std::mutex> lock(mutex_);
			data_.push(value);
			condition_.notify_one();
		}

		T pop( )
		{
			std::unique_lock<std::mutex> lock(mutex_);
			while(data_.empty())
				condition_.wait(lock);
			T value = data_.front();
			data_.pop();
			return value;
		}

		size_t size() 
		{
			std::lock_guard<std::mutex> lock(mutex_);
			return data_.size();
		}
}; 

#endif//__QUEUE__H

