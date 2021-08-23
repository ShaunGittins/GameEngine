#include "ISystem.h"

void ISystem::AddComponentReference(IComponent* component)
{
	_components.push_back(component);
}
