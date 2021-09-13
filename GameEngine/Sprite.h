#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>

class Sprite
{
public:
	Sprite(SDL_Texture* texture, SDL_FRect rect, float originX, float originY, double angle);

	SDL_Texture* _texture = NULL;
	SDL_FRect _rect;
	SDL_FPoint _rotationPoint = { 0.0f, 0.0f };
	double _angle = 0.0;
};

