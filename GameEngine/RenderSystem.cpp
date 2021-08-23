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
	for (IComponent* component : _components) {
		if (RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component)) {
			if (renderComponent->isVisible) {
				renderComponent->Render();
			}
		}
	}
}

void RenderSystem::AddComponentReference(RenderComponent* renderComponent)
{
	ISystem::AddComponentReference(renderComponent);
}
