#pragma once

#include <SDL.h>

class Score
{
public:
	Score();
	~Score() = default;

	void Draw(SDL_Surface* windowSurface);
	void UpdateScore(int score);

private:
	int m_score = 0;
	
	int m_scoreWidth = 30;
	int m_scoreHeight = 20;
	float m_positionX = m_scoreWidth * 0.5f;
	float m_positionY = m_scoreHeight * 0.5f;
};

