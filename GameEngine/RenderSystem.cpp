#include "RenderSystem.h"
#include <iostream>
#include <SDL.h>
using std::cout;
using std::endl;

RenderSystem::RenderSystem(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Render()
{
	for (RenderComponent* renderComponent : _renderComponents) {
		if (renderComponent->isVisible) {
			renderComponent->Render();
		}
	}
}

void RenderSystem::AddComponentReference(RenderComponent* renderComponent)
{
	_renderComponents.push_back(renderComponent);
}
