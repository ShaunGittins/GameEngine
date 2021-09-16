#include "RenderSystem.h"
#include "Vector2.h"
#include "Entity.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

RenderSystem::RenderSystem(SDL_Renderer* renderer, CameraComponent* camera)
{
	_renderer = renderer;
	_mainCamera = camera;
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Render()
{
	// TODO: Change this to not create another vector with casted derived class
	std::vector<RenderComponent*> renderComponents;

	for (IComponent* component : _components) {
		if (RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component)) {
			renderComponents.push_back(renderComponent);
		}
	}

	std::sort(renderComponents.begin(), renderComponents.end(), [](RenderComponent* l, RenderComponent* r) {return l->layer < r->layer; });

	for (RenderComponent* renderComponent : renderComponents) {
		if (renderComponent->isVisible) {
			Vector2 cameraVector{ _mainCamera->_cameraRect.x, _mainCamera->_cameraRect.y };
			renderComponent->Render(cameraVector);
		}
	}
}

CameraComponent* RenderSystem::GetMainCamera()
{
	return _mainCamera;
}

void RenderSystem::SetMainCamera(CameraComponent* camera)
{
	_mainCamera = camera;
}

void RenderSystem::AddComponentReference(RenderComponent* renderComponent)
{
	ISystem::AddComponentReference(renderComponent);
}

SDL_Renderer* RenderSystem::GetRenderer()
{
	return _renderer;
}
