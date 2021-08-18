#pragma once
#include "IComponent.h"
#include <SDL.h>
class SpriteComponent : public IComponent
{
public:
	SpriteComponent(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Rect spriteRect);
	~SpriteComponent();

	void Render(SDL_Renderer* renderer);

private:
	SDL_Texture* _ballBitmapTexture = NULL;
	SDL_Rect _spriteRect;
};

