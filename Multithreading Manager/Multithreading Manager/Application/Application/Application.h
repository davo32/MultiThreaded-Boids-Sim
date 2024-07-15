#pragma once
#include "glfw/glfw3.h"
#include "glm.hpp"

class Application
{
public:
	bool glfwSetup();
	bool startup();
	void update();
	void draw();
	void shutdown();
	void TerminateWindow();
	bool shutdownState() { return isShuttingdown; }

	virtual bool subStartup() { return true; }
	virtual void subUpdate() {}
	virtual void subDraw() { }

	glm::vec2 getScreenDimensions() { return glm::vec2(windowWidth, windowHeight); }

private:
	GLFWwindow* window;


	bool isShuttingdown = false;
	float windowWidth = 1080;
	float windowHeight = 720;
};

