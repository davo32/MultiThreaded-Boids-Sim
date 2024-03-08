#pragma once
#include "MTManager.h"
#include <string>
#include <iostream>


class MTLogger
{
public:
	MTLogger(MTManager* manager) : Manager(manager) {}

	void DebugLog(std::string text)
	{
		Manager->AddTask([text]()
			{
				std::cout << "[MT Logger] : " << text << "\n" << std::endl;
			},TaskPriority::Low);
	}

private:
	MTManager* Manager;
};

