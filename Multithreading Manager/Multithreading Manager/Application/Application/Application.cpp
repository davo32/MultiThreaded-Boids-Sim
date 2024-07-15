#include "../Dependencies/gl_core_4_4.h"
#include "Application.h"
#include <iostream>
#include "../Dependencies/Gizmos.h"

bool Application::glfwSetup()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window = glfwCreateWindow(windowWidth, windowHeight, "MT Boids Simulation", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		std::cout << "Failed to load the openGL functions";
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}
}

bool Application::startup()
{
	if (!glfwSetup())
	{
		std::cout << "Failed to run GLFW setup";
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

		subStartup();

	return true;
}

void Application::update()
{
	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
		subUpdate();

		glfwSwapBuffers(window);
		glfwPollEvents();
	//}

	//isShuttingdown = true;
}

void Application::draw()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	subDraw();
}

void Application::shutdown()
{
	TerminateWindow();
}

void Application::TerminateWindow()
{
	aie::Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}
