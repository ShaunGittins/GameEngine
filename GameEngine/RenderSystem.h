#pragma once
#include "RenderComponent.h"
#include <vector>
#include <SDL.h>

class RenderSystem
{
public:
	RenderSystem(SDL_Renderer* renderer);
	~RenderSystem();

	void Render();

	void AddComponentReference(RenderComponent* renderComponent);

private:
	SDL_Renderer* _renderer;
	std::vector<RenderComponent*> _renderComponents;
};

