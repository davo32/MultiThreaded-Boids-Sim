#include "SimApp.h"
#include "Gizmos.h"
#include <ext.hpp>



bool SimApp::subStartup(MTManager* manager)
{
	renderer = new aie::Renderer2D();
	font = new aie::Font("./font/consolas.ttf", 32);

	Logger = new MTLogger(manager);

	aie::Gizmos::create(255U, 255U, 65535U, 65525U);
	Logger->DebugLog("Simulation Started...");

	manager->AddTask([&]()
		{
			if (!CreateBoids(100))
			{
				return false;
			}
		},TaskPriority::High);

	

	return true;
}

void SimApp::subUpdate(MTManager* manager)
{
	aie::Gizmos::clear();

	manager->AddTask([&]()
		{
			for (auto& boid : boids)
			{
				boid.Update(boids, getScreenDimensions());
			}
		}, TaskPriority::High);
}

void SimApp::subDraw()
{
	renderer->begin();

	

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / 16 / 9, 100 / 16 / 9, -1.0f, 1.0f));
	
	renderer->drawText(font, "Press ESC to Quit", 0, 0);
	

	for (auto& boid : boids)
	{
		boid.Draw(renderer);
		
	}
	aie::Gizmos::draw2D(glm::mat4(1));
	renderer->end();
}

bool SimApp::CreateBoids(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * WIDTH;
		float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * HEIGHT;
		boids.emplace_back(x,y);
	}
	if (boids.size() == amount)
	{
		Logger->DebugLog("Boids have been created...");
		return true;
	}
	return false;
	
}