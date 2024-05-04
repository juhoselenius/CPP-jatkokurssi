#include "Ground.h"

Ground::Ground(float positionX, float positionY, b2World* gameWorld)
{
	// Physical representation of the ground
	m_groundBodyDef.type = b2_staticBody;
	m_groundBodyDef.position = b2Vec2(positionX, positionY);
	m_groundBody = gameWorld->CreateBody(&m_groundBodyDef);
	m_groundShape.SetAsBox(m_groundWidth * 0.5f, m_groundHeight * 0.5f);
	m_groundBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	m_groundBody->CreateFixture(&m_groundShape, 0.0f);

	// Visual representation of the ground
	m_groundRect.x = positionX - m_groundWidth * 0.5f;
	m_groundRect.y = positionY - m_groundHeight * 0.5f;
	m_groundRect.w = m_groundWidth;
	m_groundRect.h = m_groundHeight;
}

void Ground::Draw(SDL_Surface* windowSurface)
{
	SDL_FillRect(windowSurface, &m_groundRect, SDL_MapRGB(windowSurface->format, 0, 255, 0)); // Draw the ground with green color
}
