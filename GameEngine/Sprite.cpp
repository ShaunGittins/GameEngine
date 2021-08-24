#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_FRect rect)
{
	_texture = texture;
	_rect = rect;
}
