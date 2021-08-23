#pragma once
#include "IComponent.h"
#include <vector>

class ISystem
{
public:
	void AddComponentReference(IComponent* component);

protected:
	std::vector<IComponent*> _components;
};

