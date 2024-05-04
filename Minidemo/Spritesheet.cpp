#include "Spritesheet.h"
#include <iostream>
#include <string>

Spritesheet::Spritesheet(int column)
{
	m_spritesheetImage = SDL_LoadBMP("sprites/Ghroth_spritesheet.bmp");

	if (!m_spritesheetImage)
	{
		std::cout << "Failed to load spritesheet" << "\n";
		return;
	}
	else
	{
		std::cout << "Spritesheet loaded successfully" << "\n";
	}

	m_clip.w = m_spritesheetImage->w / column;
	m_clip.h = m_spritesheetImage->h;
}

Spritesheet::~Spritesheet()
{
	SDL_FreeSurface(m_spritesheetImage);
}

void Spritesheet::SelectSprite(int spriteIndex)
{
	m_clip.x = spriteIndex * m_clip.w;
}

void Spritesheet::DrawSelectedSprite(SDL_Surface* windowSurface, SDL_Rect* position)
{
	SDL_BlitSurface(m_spritesheetImage, &m_clip, windowSurface, position);
}
