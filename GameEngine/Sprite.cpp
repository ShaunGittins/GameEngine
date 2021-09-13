#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_FRect rect, float originX, float originY, double angle)
{
	_texture = texture;
	_rect = rect;
	_rotationPoint.x = originX;
	_rotationPoint.y = originY;
	_angle = angle;
}
