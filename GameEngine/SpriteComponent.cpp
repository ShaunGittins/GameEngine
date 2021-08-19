#include "SpriteComponent.h"
#include <iostream>

using std::cout;
using std::endl;

SpriteComponent::SpriteComponent(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Rect spriteRect)
{
	if (surface != nullptr) {
		_ballBitmapTexture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	else {
		cout << "Error with SDL_LoadBMP(): " << SDL_GetError() << endl;
	}
	SDL_FreeSurface(surface);

	_spriteRect = spriteRect;
}

SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(_ballBitmapTexture);
}

void SpriteComponent::Render(SDL_Renderer* renderer)
{
	/*
	if (SDL_RenderCopy(renderer, _ballBitmapTexture, NULL, &_spriteRect) != 0) {
		cout << "Error with SDL_RenderCopy: " << SDL_GetError() << endl;
	}*/
}
