#include "RenderSystem.h"
#include <iostream>
#include <SDL.h>
#include "Vector2.h"

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
	for (IComponent* component : _components) {
		if (RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component)) {
			if (renderComponent->isVisible) {
				Vector2 cameraVector { _mainCamera->_cameraRect.x, _mainCamera->_cameraRect.y };
				renderComponent->Render(cameraVector);
			}
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
