#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class MTLogger;

enum class TaskPriority
{
	Low,
	Normal,
	High
};


class MTManager
{
public:
	static MTManager& getInstance();

	MTLogger& GetLogger();

	//Delete copy constructor and assignment operator
	MTManager(const MTManager&) = delete;
	MTManager& operator=(const MTManager&) = delete;

	void AddTask(std::function<void()> task, TaskPriority priority = TaskPriority::Normal);

private:
	MTManager(int numThreads);
	~MTManager();

	friend class MTLogger;

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

	struct Deleter
	{
		void operator()(MTManager* manager) const
		{
			delete manager;
		}
	};

	static std::unique_ptr<MTManager, Deleter> instance;
};

