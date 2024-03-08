#pragma once
#include "glfw/glfw3.h"
#include "glm.hpp"
#include "MTManager.h"

class Application
{
public:
	bool glfwSetup();
	bool startup(MTManager* manager);
	void update(MTManager* manager);
	void draw();
	void shutdown();
	void TerminateWindow();
	bool shutdownState() { return isShuttingdown; }

	virtual bool subStartup(MTManager* manager) { return true; }
	virtual void subUpdate(MTManager* manager) {}
	virtual void subDraw() { }

	glm::vec2 getScreenDimensions() { return glm::vec2(windowWidth, windowHeight); }

private:
	GLFWwindow* window;


	bool isShuttingdown = false;
	float windowWidth = 1080;
	float windowHeight = 720;
};

