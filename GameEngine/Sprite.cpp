#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_FRect rect, float originX, float originY, double angle)
{
	_texture = texture;
	_rect = rect;
	_rotationPoint = { originX, originY };
	_angle = angle;
}
