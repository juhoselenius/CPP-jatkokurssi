#pragma once

#include <SDL.h>

class Spritesheet
{
public:
	Spritesheet() = default;
	Spritesheet(int column);
	~Spritesheet();

	void SelectSprite(int spriteIndex);
	void DrawSelectedSprite(SDL_Surface* windowSurface, SDL_Rect* position);

private:
	SDL_Rect m_clip; //!< The current player image to be drawn.
	SDL_Surface* m_spritesheetImage; //!< The spritesheet image.
};

