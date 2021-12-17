#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>

using std::string;

class Sprite
{
public:
	Sprite(string filename, SDL_Texture* texture, SDL_FRect rect, float originX, float originY, float angle): filename(filename), texture(texture), rect(rect), rotationPoint({ originX, originY }), angle(angle) {}

	string filename;
	SDL_Texture* texture = NULL;
	SDL_FRect rect;
	SDL_FPoint rotationPoint;
	float angle;
};

