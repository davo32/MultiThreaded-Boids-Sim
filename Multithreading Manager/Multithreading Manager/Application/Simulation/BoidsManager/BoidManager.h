#pragma once
#include "../Boids/Boid.h"
#include "Renderer2D.h"
#include "../../MultiThreading/MTManager.h"
#include <vector>
#include <cstdlib>
#include <ctime>


class MTLogger;

class BoidManager
{
public:
	BoidManager();
	~BoidManager();

	bool CreateBoids(int amount, float width, float height,glm::vec2 ScreenDimensions);
	void UpdateBoids(const glm::vec2& screenDimensions);
	void DrawBoids(aie::Renderer2D* renderer);

private:
	std::vector<Boid*> boids;
	std::mutex boidMutex;
	void InitRandomSeed();
	void CheckBoidInteraction();
};

