#include "MTManager.h"

MTManager::MTManager(int numThreads) : isRunning(true)
{
	for (int i = 0; i < numThreads; ++i)
	{
		threads.emplace_back(std::bind(&MTManager::workerThread, this));
	}
}

MTManager::~MTManager()
{
	isRunning = false;
	cv.notify_all();
	for (auto& thread : threads)
	{
		thread.join();
	}
}

void MTManager::AddTask(std::function<void()> task,TaskPriority priority)
{
	std::lock_guard<std::mutex> lock(mutex);
	tasks.push({ task,priority });
	cv.notify_one();
}

void MTManager::workerThread()
{
	while (isRunning)
	{
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [this]() {return !tasks.empty() || !isRunning; });
		if (!isRunning) return;
		auto task = tasks.top();
		tasks.pop();
		lock.unlock();
		task.task();
	}
}