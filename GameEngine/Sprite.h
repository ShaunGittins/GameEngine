#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class Sprite
{
public:
	Sprite(SDL_Texture* texture, SDL_FRect rect);

	SDL_Texture* _texture = NULL;
	SDL_FRect _rect;
};

