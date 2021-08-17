#pragma once
#include "IComponent.h"
#include <SDL.h>

class RenderComponent : public IComponent
{
public:
	RenderComponent();
	RenderComponent(bool visible);

	void Render(SDL_Renderer* renderer);

	void ToggleVisibility();

	bool isVisible;
};

