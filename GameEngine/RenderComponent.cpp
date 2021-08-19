#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include <iostream>

RenderComponent::RenderComponent(SDL_Renderer* renderer)
{
	_renderer = renderer;
	isVisible = true;
}

RenderComponent::RenderComponent(SDL_Renderer* renderer, bool visible)
{
	_renderer = renderer;
	isVisible = visible;
}

void RenderComponent::Render()
{
	if (parent->GetComponent<TransformComponent>()) {
		TransformComponent* tc = parent->GetComponent<TransformComponent>();
		SDL_FRect parentRect{ tc->_position._x, tc->_position._y, tc->_scale._x, tc->_scale._y };

		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderFillRectF(_renderer, &parentRect);
	}
}

void RenderComponent::AddSprite(SDL_Surface* surface, SDL_Rect spriteRect)
{
	if (surface != nullptr) {
		_ballBitmapTexture = SDL_CreateTextureFromSurface(_renderer, surface);
	}
	else {
		std::cout << "Error with SDL_LoadBMP(): " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);

	//_spriteRect = spriteRect;
}

void RenderComponent::AddRect(SDL_Rect spriteRect)
{
	_rects.push_back(spriteRect);
}

void RenderComponent::ToggleVisibility()
{
	isVisible = !isVisible;
}
