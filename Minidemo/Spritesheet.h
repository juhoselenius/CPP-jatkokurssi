#pragma once

#include <SDL.h>

class Spritesheet
{
public:
	Spritesheet() = default;
	Spritesheet(const char* path, int row, int column);
	~Spritesheet();

	void SelectSprite(int x, int y);
	void DrawSelectedSprite(SDL_Surface* windowSurface, SDL_Rect* position);

private:
	SDL_Rect m_clip;
	SDL_Surface* m_spritesheetImage;

	int m_startX;
	int m_startY;
};

