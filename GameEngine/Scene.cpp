#include "Scene.h"
#include "NameComponent.h"

Scene::Scene(SDL_Renderer* renderer, CameraComponent* mainCamera)
{
	_renderSystem = new RenderSystem(renderer, mainCamera);
	_transformSystem = new TransformSystem();
}

Scene::~Scene()
{
	delete _renderSystem;
	delete _transformSystem;

	for (auto& entity : _entities) {
		delete entity;
	}
	_entities.clear();
}

void Scene::AddEntityToScene(Entity* entity)
{
	if (VelocityComponent* velocityComponent = entity->GetComponent<VelocityComponent>()) {
		_transformSystem->AddComponentReference(velocityComponent);
	}

	if (RenderComponent* renderComponent = entity->GetComponent<RenderComponent>()) {
		_renderSystem->AddComponentReference(renderComponent);
	}
	
	_entities.push_back(entity);
}

Entity* Scene::GetEntityByName(std::string name)
{
	// TODO: Add unique names
	for (auto& entity : _entities) {
		NameComponent* nameComponent = entity->GetComponent<NameComponent>();
		if (nameComponent) {
			if (nameComponent->_name == name) {
				return entity;
			}
		}
	}
	return nullptr;
}

Entity* Scene::GetEntityByID(uint64_t id)
{
	for (auto& entity : _entities) {
		if (entity->_id = id) {
			return entity;
		}
	}
	return nullptr;
}

void Scene::SetMainCamera(CameraComponent* mainCamera)
{
	_renderSystem->SetMainCamera(mainCamera);
}

CameraComponent* Scene::GetMainCamera()
{
	return _renderSystem->GetMainCamera();
}

Vector2 Scene::CameraToWorldPosition(Vector2 positionInCamera)
{
	return { GetMainCamera()->_cameraRect.x + positionInCamera._x, GetMainCamera()->_cameraRect.y + positionInCamera._y };
}

void Scene::Update()
{
	_transformSystem->Update();
}

void Scene::Render()
{
	_renderSystem->Render();
}
