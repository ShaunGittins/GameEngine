#pragma once
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "ISystem.h"
#include <vector>
#include <SDL.h>

class RenderSystem : ISystem
{
public:
	RenderSystem(SDL_Renderer* renderer, CameraComponent* mainCamera);
	~RenderSystem();

	void Render();

	CameraComponent* GetMainCamera();
	void SetMainCamera(CameraComponent* camera);

	void AddComponentReference(RenderComponent* renderComponent);

private:
	SDL_Renderer* _renderer;
	CameraComponent* _mainCamera;
};

