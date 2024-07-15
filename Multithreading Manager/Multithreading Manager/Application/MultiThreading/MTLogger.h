#pragma once
#include <string>
#include <iostream>

class MTManager;

class MTLogger
{
public:
	MTLogger(MTManager* manager) : Manager(manager) {}

	//Delete copy and assignment operators
	MTLogger(const MTLogger&) = delete;
	MTLogger& operator=(const MTLogger&) = delete;

	void DebugLog(std::string text);
	

private:
	MTManager* Manager;
};

