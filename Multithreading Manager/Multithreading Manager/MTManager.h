#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

enum class TaskPriority
{
	Low,
	Normal,
	High
};


class MTManager
{
public:
	MTManager(int numThreads);
	~MTManager();

	void AddTask(std::function<void()> task, TaskPriority priority = TaskPriority::Normal);

private:
	struct Task
	{
		std::function<void()> task;
		TaskPriority priority;
	};

	struct TaskCompare
	{
		bool operator()(const Task& left, const Task& right) const
		{
			return left.priority < right.priority;
		}
	};

	std::mutex mutex;
	std::vector<std::thread> threads;
	std::priority_queue<Task, std::vector<Task>, TaskCompare> tasks;
	std::condition_variable cv;
	bool isRunning;

	void workerThread();
};

