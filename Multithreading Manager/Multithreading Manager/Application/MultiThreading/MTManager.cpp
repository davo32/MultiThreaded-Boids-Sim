#include "MTManager.h"
#include "MTLogger.h"

std::unique_ptr<MTManager, MTManager::Deleter> MTManager::instance = nullptr;

MTManager::MTManager(int numThreads) : isRunning(true)
{
	for (int i = 0; i < numThreads; ++i)
	{
		threads.emplace_back(std::bind(&MTManager::workerThread, this));
	}
}

MTManager::~MTManager()
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		isRunning = false;
	}

	cv.notify_all();

	for (auto& thread : threads)
	{
		thread.join();
	}
}

MTManager& MTManager::getInstance()
{
	static std::once_flag onceFlag;
	std::call_once(onceFlag, []()
		{
			instance.reset(new MTManager(std::thread::hardware_concurrency()));
		});
	return *instance;
}

MTLogger& MTManager::GetLogger()
{
	static MTLogger logger(this);
	return logger;
}

void MTManager::AddTask(std::function<void()> task,TaskPriority priority)
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		tasks.push({ task,priority });
	}

	cv.notify_one();
}

void MTManager::workerThread()
{
	while (isRunning)
	{
		Task task;
		{
			std::unique_lock<std::mutex> lock(mutex);
			cv.wait(lock, [this]() 
				{
					return !tasks.empty() || !isRunning; 
				});
			if (!isRunning && tasks.empty())
			{
				return;
			}
			task = tasks.top();
			tasks.pop();
		}
		task.task();
	}
}