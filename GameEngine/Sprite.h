#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class Sprite
{
public:
	Sprite(SDL_Texture* texture, SDL_Rect rect);

	SDL_Texture* _texture = NULL;
	SDL_Rect _rect;
};

