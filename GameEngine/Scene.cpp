#include "Scene.h"
#include "NameComponent.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	for (auto& entity : _entities) {
		delete entity;
	}
	_entities.clear();
}

void Scene::AddEntityToScene(Entity* entity)
{
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
