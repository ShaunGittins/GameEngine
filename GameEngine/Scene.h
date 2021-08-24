#pragma once
#include <vector>
#include <string>
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();

	void AddEntityToScene(Entity* entity);

	Entity* GetEntityByName(std::string name);

	Entity* GetEntityByID(uint64_t id);

private:
	std::vector<Entity*> _entities;
};

