#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(float positionX, float positionY, b2World* gameWorld)
{
	m_world = gameWorld;
	
	// Physical representation of the upper obstacle
	m_upperObstacleBodyDef.position = b2Vec2(positionX, positionY - m_obstacleHeight * 0.5f - gapHalfHeight);
	m_upperObstacleBody = gameWorld->CreateBody(&m_upperObstacleBodyDef);
	m_upperObstacleShape.SetAsBox(m_obstacleWidth * 0.5f, m_obstacleHeight * 0.5f);
	m_upperObstacleBody->CreateFixture(&m_upperObstacleShape, 0.0f);

	// Physical representation of the lower obstacle
	m_lowerObstacleBodyDef.position = b2Vec2(positionX, positionY + m_obstacleHeight * 0.5f + gapHalfHeight);
	m_lowerObstacleBody = gameWorld->CreateBody(&m_lowerObstacleBodyDef);
	m_lowerObstacleShape.SetAsBox(m_obstacleWidth * 0.5f, m_obstacleHeight * 0.5f);
	m_lowerObstacleBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	m_lowerObstacleBody->CreateFixture(&m_lowerObstacleShape, 0.0f);

	// Visual representation of the obstacle
	m_upperObstacleRect.x = positionX - m_obstacleWidth * 0.5f;
	m_upperObstacleRect.y = positionY - m_obstacleHeight - gapHalfHeight;
	m_upperObstacleRect.w = m_obstacleWidth;
	m_upperObstacleRect.h = m_obstacleHeight;

	// Visual representation of the obstacle
	m_lowerObstacleRect.x = positionX - m_obstacleWidth * 0.5f;
	m_lowerObstacleRect.y = positionY + gapHalfHeight;
	m_lowerObstacleRect.w = m_obstacleWidth;
	m_lowerObstacleRect.h = m_obstacleHeight;

	m_upperX = positionX;
	m_lowerX = positionX;
}

void Obstacle::Update(double deltaTime)
{
	// Move the obstacle from right to left by decreasing its x-coordinate
	m_upperX -= m_speed * deltaTime;
	m_lowerX -= m_speed * deltaTime;

	// Update the Box2D body position
	m_upperObstacleBody->SetTransform(b2Vec2(m_upperX, m_upperObstacleBody->GetPosition().y), 0);
	m_lowerObstacleBody->SetTransform(b2Vec2(m_lowerX, m_lowerObstacleBody->GetPosition().y), 0);

	// Update the obstacles' position
	b2Vec2 upperPosition = m_upperObstacleBody->GetPosition();
	m_upperObstacleRect.x = upperPosition.x - m_upperObstacleRect.w * 0.5f;
	b2Vec2 lowerPosition = m_lowerObstacleBody->GetPosition();
	m_lowerObstacleRect.x = lowerPosition.x - m_lowerObstacleRect.w * 0.5f;
}

void Obstacle::Draw(SDL_Surface* windowSurface)
{
	SDL_FillRect(windowSurface, &m_upperObstacleRect, SDL_MapRGB(windowSurface->format, 255, 0, 0)); // Draw the ground with red color
	SDL_FillRect(windowSurface, &m_lowerObstacleRect, SDL_MapRGB(windowSurface->format, 255, 0, 0)); // Draw the ground with red color
}
