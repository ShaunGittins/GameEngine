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
	// By default use parent location as origin point if parent has transformComponent
	// TODO: Allow optional 0x, 0y scene origin

	float originX = 0.0f;
	float originY = 0.0f;

	if (parent->GetComponent<TransformComponent>()) {
		TransformComponent* parentTransform = parent->GetComponent<TransformComponent>();
		originX = parentTransform->_position._x;
		originY = parentTransform->_position._y;
	}

	for (SDL_Rect rect : _rects) {
		SDL_FRect rectToDraw{ originX + rect.x, originY + rect.y, rect.w, rect.h };
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderFillRectF(_renderer, &rectToDraw);
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
