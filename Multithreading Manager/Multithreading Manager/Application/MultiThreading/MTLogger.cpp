#include "MTLogger.h"
#include "MTManager.h"

void MTLogger::DebugLog(std::string text)
{
	if (Manager == nullptr)
	{
		throw std::runtime_error("MTManager instance not Set.");
	}
	Manager->AddTask([text]()
	{
		std::cout << "[MT Logger] : " << text << "\n" << std::endl;
	}, TaskPriority::Low);
}
