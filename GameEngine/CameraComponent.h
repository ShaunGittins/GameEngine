#pragma once
#include "IComponent.h"
#include <SDL_rect.h>
#include <SDL.h>

class CameraComponent : public IComponent
{
public: 
	CameraComponent(SDL_Rect cameraRect);
	~CameraComponent();

	void DebugDraw(SDL_Renderer* renderer);

private:
	SDL_Rect _cameraRect;
};

