#pragma once
#include "glm.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "../../Dependencies/Renderer2D.h"
#include "../../Dependencies/Texture.h"
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


const float WIDTH = 5.0f;
const float HEIGHT = 8.0f;
const int NUM_BOIDS = 100;
const float MAX_SPEED = 0.2f;
const float NEIGHBOR_RADIUS = 30.f;
const float SEPARATION_DISTANCE = 15.0f;
const float ALIGNMENT_FACTOR = 0.1f;
const float COHESION_FACTOR = 0.5f;
const float SEPARATION_FACTOR = 0.5f;

class Boid
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	float rotation; // rotation angle
	float angularVelocity; //velocity
	float maxRotationSpeed;
	static constexpr float InteractionRange = 30.0f;

	Boid(float minX,float minY,float maxX, float maxY) : rotation(0.0f),angularVelocity(0.0f),maxRotationSpeed(0.0f)
	{

		// Initialize random seed based on current time
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// Generate random position within specified range
		float x = minX + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (maxX - minX);
		float y = minY + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * (maxY - minY);

		position = glm::vec2(x, y);

		float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * M_PI;
		velocity = glm::vec2(std::cos(angle), std::sin(angle)) * MAX_SPEED;
	}

	void Update(const std::vector<Boid>& boids,glm::vec2 SD);
	void Draw(aie::Renderer2D* render);

	glm::vec2 getPosition();


	// ToDo:
	void Exit(Boid& boid);
	// ToDo:
	void Enter(Boid& boid);

private:
	glm::vec2 normalize(glm::vec2 vec);

	void WrapBoidPosition(glm::vec2 SD);
	void WrapRotation();
	void BoidMovementLogic(const std::vector<Boid>& boids);

	std::vector<const Boid*> nearbyBoids;

	// ToDo:
	bool IsInList(Boid& boid);
};

