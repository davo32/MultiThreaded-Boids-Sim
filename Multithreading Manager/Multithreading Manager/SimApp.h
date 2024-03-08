#pragma once
#include "Application.h"
#include "Boid.h"
#include "MTLogger.h"
#include "Renderer2D.h"
#include "Font.h"

class SimApp : public Application
{
public:
	SimApp() {}
	virtual ~SimApp() 
	{
		delete Logger;
		delete renderer;
		//delete font;
	}
	bool subStartup(MTManager* manager) override;
	void subUpdate(MTManager* manager) override;
	void subDraw() override;

private:
	bool CreateBoids(int amount);
	std::vector<Boid> boids;

	glm::mat4 m_view;
	glm::mat4 m_projection;

	MTLogger* Logger;

	aie::Renderer2D* renderer;
	aie::Font* font;


};

