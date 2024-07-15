#include "Boid.h"
#include "../../Dependencies/Gizmos.h"
#include <iostream>


void Boid::Exit(Boid& boid)
{
    auto it = std::remove(nearbyBoids.begin(), nearbyBoids.end(), &boid);
    if (it != nearbyBoids.end())
    {
        nearbyBoids.erase(it);
    }
}

void Boid::Enter(Boid& boid)
{
    auto it = std::find(nearbyBoids.begin(), nearbyBoids.end(), &boid);
    if (it == nearbyBoids.end())
    {
        nearbyBoids.push_back(&boid);
    }
}

glm::vec2 Boid::normalize(glm::vec2 vec)
{
	float length = std::hypot(vec.x, vec.y);
	if (length > 0)
	{
		vec /= length;
	}
	return vec;
}

void Boid::WrapBoidPosition(glm::vec2 SD)
{
    // Keep boid within screen bounds
    if (position.x < 0) {
        position.x = SD.x;
    }
    else if (position.x > SD.x) {
        position.x = 0;
    }

    if (position.y < 0) {
        position.y = SD.y;
    }
    else if (position.y > SD.y) {
        position.y = 0;
    }
}

void Boid::WrapRotation()
{
    rotation = atan2(velocity.x, velocity.y);
    // Keep rotation within [-pi, pi] range
    while (rotation > M_PI) rotation -= 2 * M_PI;
    while (rotation < -M_PI) rotation += 2 * M_PI;
}

void Boid::BoidMovementLogic(const std::vector<Boid>& boids)
{
    glm::vec2 separation(0.0f, 0.0f);
    glm::vec2 alignment(0.0f, 0.0f);
    glm::vec2 cohesion(0.0f, 0.0f);
    int boidCount = boids.size();

    for (const auto& boid : boids) {
        float distance = std::hypot(position.x - boid.position.x, position.y - boid.position.y);
        if (&boid != this && distance < InteractionRange) {
            if (distance < SEPARATION_DISTANCE) {
                separation += position - boid.position;
            }
            alignment += boid.velocity;
            cohesion += boid.position;
        }
    }

    if (boidCount > 0)
    {
        separation /= static_cast<float>(boidCount);
        separation = normalize(separation) * MAX_SPEED;
        alignment /= static_cast<float>(boidCount);
        alignment = normalize(alignment) * MAX_SPEED;
        cohesion /= static_cast<float>(boidCount);
        cohesion = normalize(cohesion) * MAX_SPEED;
    }

    velocity += separation * SEPARATION_FACTOR + alignment * ALIGNMENT_FACTOR + cohesion * COHESION_FACTOR;
    if (glm::length(velocity) > MAX_SPEED) {
        velocity = normalize(velocity) * MAX_SPEED;
    }
    position += velocity;
}

void Boid::Update(const std::vector<Boid>& boids,glm::vec2 SD)
{
    BoidMovementLogic(boids);
    WrapRotation();
    WrapBoidPosition(SD);
}

void Boid::Draw(aie::Renderer2D* render)
{
    render->setRenderColour(1,0,0,1);
    render->drawTriangle(position.x, position.y, 8.0f, 1.0f,rotation);
}

glm::vec2 Boid::getPosition()
{
    return glm::vec2();
}

/*
Boid has a radius
Boid Manager <-- Track all boids. 
- Loops through each boid and checks its position to the other boids.
  - If the boid you are checking against is out of range call the boids exit 
    function with the boid as a pram to be removed from its internal list.
  - If a boid is its range pass it through as enter. That boid will check if its already in its list
       - If its not in the list add it
       - If its in the list ignore it


 ToDo: After add quadtrees for spatial partitioning
*/
