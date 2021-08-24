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

RenderComponent::~RenderComponent()
{
	for (Sprite* sprite : _sprites) {
		delete sprite;
	}
	_sprites.clear();
}

void RenderComponent::Render(Vector2 cameraPos)
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

	for (const SDL_FRect &rect : _rects) {
		SDL_FRect drawRect{ originX + rect.x - cameraPos._x, originY + rect.y - cameraPos._y, rect.w, rect.h };
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderFillRectF(_renderer, &drawRect);
	}

	for (Sprite* sprite : _sprites) {
		SDL_FRect drawRect{ originX + sprite->_rect.x - cameraPos._x, originY + sprite->_rect.y - cameraPos._y, sprite->_rect.w, sprite->_rect.h };
		if (SDL_RenderCopyF(_renderer, sprite->_texture, NULL, &drawRect) != 0) {
			std::cout << "Error with SDL_RenderCopy: " << SDL_GetError() << std::endl;
		}
	}
}

void RenderComponent::AddSprite(SDL_Surface* surface, SDL_FRect spriteRect)
{
	Sprite* mySprite{};

	if (surface != nullptr) {
		mySprite = new Sprite(SDL_CreateTextureFromSurface(_renderer, surface), spriteRect);
	}
	else {
		std::cout << "Error with SDL_LoadBMP(): " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);

	
	if (mySprite != nullptr) {
		_sprites.push_back(mySprite);
	}
}

void RenderComponent::AddRect(SDL_FRect rect)
{
	_rects.push_back(rect);
}

void RenderComponent::ToggleVisibility()
{
	isVisible = !isVisible;
}
