#include "RenderSystem.h"
#include <iostream>
#include <SDL.h>
using std::cout;
using std::endl;

RenderSystem::RenderSystem(SDL_Renderer* renderer)
{
	_renderer = renderer;
	cout << "#Render system init" << endl;
}

RenderSystem::~RenderSystem()
{
	cout << "#Render system delete" << endl;
}

void RenderSystem::Render()
{
	for (RenderComponent* renderComponent : _renderComponents) {
		if (renderComponent->isVisible) {
			renderComponent->Render(_renderer);
		}
	}
}

void RenderSystem::AddComponentReference(RenderComponent* renderComponent)
{
	_renderComponents.push_back(renderComponent);
}
