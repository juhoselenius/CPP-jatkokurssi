#include "Spritesheet.h"
#include <iostream>

Spritesheet::Spritesheet(const char* path, int row, int column)
{
	m_spritesheetImage = SDL_LoadBMP(path);

	if (!m_spritesheetImage)
	{
		std::cout << "Failed to load image" << "\n";
		std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
		return;
	}
	else
	{
		m_clip.w = m_spritesheetImage->w / column;
		m_clip.h = m_spritesheetImage->h / row;
		std::cout << "Image loaded successfully." << "\n"; // Add this line
	}
}

Spritesheet::~Spritesheet()
{
	SDL_FreeSurface(m_spritesheetImage);
}

void Spritesheet::SelectSprite(int x, int y)
{
	m_clip.x = x * m_clip.w;
	m_clip.y = y * m_clip.h;
}

void Spritesheet::DrawSelectedSprite(SDL_Surface* windowSurface, SDL_Rect* position)
{
	if (m_spritesheetImage != nullptr)
	{
		SDL_BlitSurface(m_spritesheetImage, &m_clip, windowSurface, position);
	}
	else
	{
		std::cout << "Failed to draw sprite" << "\n";
	}
}
