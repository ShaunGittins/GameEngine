#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

RenderComponent::RenderComponent()
{
	isVisible = true;
}

RenderComponent::RenderComponent(bool visible)
{
	isVisible = visible;
}

void RenderComponent::Render(SDL_Renderer* renderer)
{
	if (parent->GetComponent<TransformComponent>()) {
		TransformComponent* tc = parent->GetComponent<TransformComponent>();
		SDL_FRect rect;
		rect.x = tc->_position._x;
		rect.y = tc->_position._y;
		rect.w = tc->_scale._x;
		rect.h = tc->_scale._y;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRectF(renderer, &rect);
	}
}

void RenderComponent::ToggleVisibility()
{
	isVisible = !isVisible;
}
