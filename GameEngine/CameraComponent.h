#pragma once
#include "IComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include <SDL_rect.h>
#include <SDL.h>

class CameraComponent : public IComponent
{
public: 
	CameraComponent(SDL_FRect cameraRect);
	~CameraComponent();

	SDL_FRect _cameraRect;
};

