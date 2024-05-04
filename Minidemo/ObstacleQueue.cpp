#include "ObstacleQueue.h"
#include <iostream>
#include <algorithm>

ObstacleQueue::ObstacleQueue(float screenWidth, float screenHeight, b2World* gameWorld)
{
	m_world = gameWorld;
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;
}

void ObstacleQueue::SpawnObstacle()
{
	// Randomly generate a gap position
	float gapPositionY = rand() % (m_screenHeight - 200) + 100;
	
	Obstacle obstacle((float)(m_screenWidth + 40), gapPositionY, m_world);
	m_obstacleQueue.push_back(obstacle);
}

void ObstacleQueue::Update(double deltaTime)
{
	m_currentTime = SDL_GetTicks();

	if (m_currentTime - m_lastSpawnTime > m_spawnInterval)
	{
		SpawnObstacle();
		m_lastSpawnTime = m_currentTime;
	}

	// Update the obstacles with a !!! lambda function !!!
	std::for_each(m_obstacleQueue.begin(), m_obstacleQueue.end(), [&](Obstacle& it)
		{
			it.Update(deltaTime);
			if (it.m_upperX < -40)
				{
					m_obstacleQueue.pop_front();
				}
	});

	// Update the obstacles
	//for (auto& it : m_obstacleQueue)
	//{
	//	it.Update(deltaTime);

	//	// If the obstacle is off the screen, destroy it
	//	if (it.m_upperX < -40)
	//	{
	//		//m_obstacleQueue.front().m_world->DestroyBody(it.m_upperObstacleBody);
	//		//m_obstacleQueue.front().m_world->DestroyBody(it.m_lowerObstacleBody);
	//		m_obstacleQueue.pop_front();
	//	}
	//}
}

void ObstacleQueue::Draw(SDL_Surface* windowSurface)
{
	for (auto it : m_obstacleQueue)
	{
		it.Draw(windowSurface);
	}
}

void ObstacleQueue::Reset()
{
	m_obstacleQueue.clear();
	m_lastSpawnTime = m_currentTime;
}
