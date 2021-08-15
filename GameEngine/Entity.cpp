#include "Entity.h"

Entity::~Entity()
{
	for (auto& component : _components) {
		delete component;
	}
	_components.clear();
}

void Entity::AddComponent(IComponent* component)
{
	component->parent = this;
	_components.push_back(component);
}
