#include "SimApp.h"
#include "Gizmos.h"
#include "../../MultiThreading/MTLogger.h"
#include <ext.hpp>



bool SimApp::subStartup()
{
	boidManager = new BoidManager();
	renderer = new aie::Renderer2D();
	font = new aie::Font("./font/consolas.ttf", 32);

	aie::Gizmos::create(255U, 255U, 65535U, 65525U);
	MTManager::getInstance().GetLogger().DebugLog("Simulation Started...");

	MTManager::getInstance().AddTask([&]()
		{
			if (!boidManager->CreateBoids(100, 5.0f, 8.0f,getScreenDimensions()))
			{
				return false;
			}
		},TaskPriority::High);

	return true;
}

void SimApp::subUpdate()
{
	aie::Gizmos::clear();
	boidManager->UpdateBoids(getScreenDimensions());
	
}

void SimApp::subDraw()
{
	renderer->begin();

	

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / 16 / 9, 100 / 16 / 9, -1.0f, 1.0f));
	
	renderer->drawText(font, "Press ESC to Quit", 0, 0);
	
	boidManager->DrawBoids(renderer);
	
	aie::Gizmos::draw2D(glm::mat4(1));
	renderer->end();
}

