#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include <SDL_render.h>
#include "CameraComponent.h"
#include "RenderSystem.h"
#include "TransformSystem.h"

class Scene
{
public:
	Scene(SDL_Renderer* renderer, CameraComponent* mainCamera);
	~Scene();

	void AddEntityToScene(Entity* entity);
	Entity* GetEntityByName(std::string name);
	Entity* GetEntityByID(uint64_t id);

	void SetMainCamera(CameraComponent* mainCamera);
	CameraComponent* GetMainCamera();

	Vector2 CameraToWorldPosition(Vector2 positionInCamera);

	void Update();
	void Render();

private:
	std::vector<Entity*> _entities;

	RenderSystem* _renderSystem;
	TransformSystem* _transformSystem;
};

