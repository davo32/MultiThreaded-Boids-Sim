#pragma once
#include "../Application.h"
#include "../../Simulation/Boids/Boid.h"
#include "../../MultiThreading/MTManager.h"
#include "../../Dependencies/Renderer2D.h"
#include "../../Dependencies/Font.h"
#include "../../Simulation/BoidsManager/BoidManager.h"

class SimApp : public Application
{
public:
	SimApp() {}
	virtual ~SimApp() 
	{
		delete renderer;
		//delete font;
	}
	bool subStartup() override;
	void subUpdate() override;
	void subDraw() override;

private:
	BoidManager* boidManager;
	std::vector<Boid> boids;

	glm::mat4 m_view;
	glm::mat4 m_projection;


	aie::Renderer2D* renderer;
	aie::Font* font;


};

