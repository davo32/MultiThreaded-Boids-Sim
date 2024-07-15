#pragma once
#include "../Boids/Boid.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../../Dependencies/Renderer2D.h"
#include "../../MultiThreading/MTManager.h"

class MTLogger;

class BoidManager
{
public:
	BoidManager();
	~BoidManager();

	bool CreateBoids(int amount, float width, float height);
	void UpdateBoids(const glm::vec2& screenDimensions);
	void DrawBoids(aie::Renderer2D* renderer);

private:
	std::vector<Boid> boids;
	std::mutex boidMutex;
	void InitRandomSeed();
	void CheckBoidInteraction();
};

