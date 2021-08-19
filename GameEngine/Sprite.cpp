#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture, SDL_Rect rect)
{
	_texture = texture;
	_rect = rect;
}
