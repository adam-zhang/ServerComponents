#ifndef __THREADPOOL__H
#define __THREADPOOL__H

#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>

class ThreadPool
{
public:
	explicit ThreadPool(int count);
	ThreadPool(const ThreadPool&) =delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	~ThreadPool();
public:
	using Task = std::function<void()>;
public:
	void start();
	void stop();
	void append(const Task& task);
private:
	int threadCount_;
	std::vector<std::thread> threads_;
	std::mutex mutex_;
	std::queue<Task> tasks_;
	std::condition_variable condition_;
	std::atomic<bool> isRunning_;
private:
	void work();
};
#endif//__THREADPOOL__H

