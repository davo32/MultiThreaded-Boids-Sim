#include "Boid.h"
#include "Gizmos.h"
#include <iostream>

glm::vec2 Boid::normalize(glm::vec2 vec)
{
	float length = std::hypot(vec.x, vec.y);
	if (length > 0)
	{
		vec /= length;
	}
	return vec;
}

void Boid::Update(const std::vector<Boid>& boids,glm::vec2 SD)
{
	glm::vec2 separation(0.0f, 0.0f);
	glm::vec2 alignment(0.0f, 0.0f);
	glm::vec2 cohesion(0.0f, 0.0f);
	
	int separationCount = 0;
	int alignmentCount = 0;
	int cohesionCount = 0;

    for (const auto& boid : boids) {
        float distance = std::hypot(position.x - boid.position.x, position.y - boid.position.y);
        if (&boid != this && distance < NEIGHBOR_RADIUS) {
            // Separation
            if (distance < SEPARATION_DISTANCE) {
                separation += position - boid.position;
                separationCount++;
            }
            // Alignment
            alignment += boid.velocity;
            alignmentCount++;
            // Cohesion
            cohesion += boid.position;
            cohesionCount++;
        }
    }

    if (separationCount > 0) {
        separation /= static_cast<float>(separationCount);
        separation = normalize(separation) * MAX_SPEED;
    }
    if (alignmentCount > 0) {
        alignment /= static_cast<float>(alignmentCount);
        alignment = normalize(alignment) * MAX_SPEED;
    }
    if (cohesionCount > 0) {
        cohesion /= static_cast<float>(cohesionCount);
        cohesion = normalize(cohesion) * MAX_SPEED;
    }

    velocity += separation * SEPARATION_FACTOR + alignment * ALIGNMENT_FACTOR + cohesion * COHESION_FACTOR;
    if (std::hypot(velocity.x, velocity.y) > MAX_SPEED) {
        velocity = normalize(velocity) * MAX_SPEED;
    }
    position += velocity;

    glm::vec2 direction = normalize(velocity);
    float targetRotation = std::atan2(direction.y, direction.x);
    float angleDifference = targetRotation - rotation;
    while (angleDifference > M_PI) angleDifference -= 2 * M_PI;
    while (angleDifference < -M_PI) angleDifference += 2 * M_PI;

    angularVelocity = glm::clamp(angleDifference, -maxRotationSpeed, maxRotationSpeed);
    rotation += angularVelocity;

    // Limit acceleration
    float maxAcceleration = 0.1f;
    glm::vec2 acceleration = (separation * SEPARATION_FACTOR + alignment * ALIGNMENT_FACTOR + cohesion * COHESION_FACTOR);
    float accelerationMagnitude = glm::length(acceleration);

    if (accelerationMagnitude > maxAcceleration) {
        acceleration = glm::normalize(acceleration) * maxAcceleration;
    }

    velocity += acceleration;

    // Limit speed
    if (glm::length(velocity) > MAX_SPEED) {
        velocity = glm::normalize(velocity) * MAX_SPEED;
    }


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

void Boid::Draw(aie::Renderer2D* render)
{
    render->setRenderColour(1,0,0,1);
    render->drawCircle(position.x, position.y, 5);
}
