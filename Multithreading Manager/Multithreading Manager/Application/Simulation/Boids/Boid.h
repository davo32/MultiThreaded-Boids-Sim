#pragma once
#include "glm.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "Renderer2D.h"
#include "Texture.h"
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

	Boid(float X, float Y, std::vector<Boid*> allBoids);


	void Update(glm::vec2 SD);
	void Draw(aie::Renderer2D* render);

	glm::vec2 getPosition();


	// ToDo:
	void Exit(Boid& boid);
	// ToDo:
	void Enter(Boid& boid);

private:
	glm::vec2 normalize(glm::vec2 vec);

	void UpdateNearbyBoids();

	void WrapBoidPosition(glm::vec2 SD);
	void WrapRotation();
	void BoidMovementLogic();

	std::vector<Boid*> nearbyBoids;
	std::vector<Boid*> AllBoids;


	// ToDo:
	bool IsInList(Boid& boid);
};

