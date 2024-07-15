#include "BoidManager.h"
#include "../../MultiThreading/MTLogger.h"

BoidManager::BoidManager()
{
	InitRandomSeed();
}

BoidManager::~BoidManager()
{
}

bool BoidManager::CreateBoids(int amount, float width, float height)
{
	for (int i = 0; i < amount; ++i)
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * width;
		float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * height;
		// Initialize boid with random position, initial velocity, and rotation
		float initialVelocity = MAX_SPEED;  // Adjust as needed
		float initialRotation = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2 * M_PI;  // Random angle in radians
		boids.emplace_back(x, y, initialVelocity, initialRotation);
	}
	if (boids.size() == amount)
	{
		MTManager::getInstance().GetLogger().DebugLog("Boids have been created...");
		return true;
	}
	return false;
}

void BoidManager::UpdateBoids(const glm::vec2& screenDimensions)
{
	//CheckBoidInteraction();

	MTManager::getInstance().AddTask([&]()
		{
			std::lock_guard<std::mutex> lock(boidMutex);
			for (auto& boid : boids)
			{
				boid.Update(boids, screenDimensions);
			}
		}, TaskPriority::High);
}

void BoidManager::DrawBoids(aie::Renderer2D* renderer)
{
	std::lock_guard<std::mutex> lock(boidMutex);
	for (auto& boid : boids)
	{
		boid.Draw(renderer);

	}
}

void BoidManager::InitRandomSeed()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void BoidManager::CheckBoidInteraction()
{
	MTManager::getInstance().AddTask([&]()
		{
			std::lock_guard<std::mutex> lock(boidMutex);
			for (auto& boid : boids)
			{
				for (auto& other : boids)
				{
					if (&boid != &other) // Don't compare a boid to itself
					{
						float distance = glm::distance(boid.getPosition(), other.getPosition());
						if (distance < Boid::InteractionRange)
						{
							boid.Enter(other); // Function to handle boid entering interaction range
						}
						else
						{
							boid.Exit(other); // Function to handle boid exiting interaction range
						}
					}
				}
			}
		}, TaskPriority::Normal);
}
