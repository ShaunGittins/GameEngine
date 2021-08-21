#include "CameraComponent.h"

CameraComponent::CameraComponent(SDL_Rect cameraRect)
{
	_cameraRect = cameraRect;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::DebugDraw(SDL_Renderer* renderer)
{
	SDL_RenderDrawRect(renderer, &_cameraRect);
}
