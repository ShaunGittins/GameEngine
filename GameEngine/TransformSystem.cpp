#include "TransformSystem.h"
#include "TransformComponent.h"
#include "Entity.h"

TransformSystem::TransformSystem()
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::Update()
{
	for (IComponent* component : _components) {
		if (VelocityComponent* velocityComponent = dynamic_cast<VelocityComponent*>(component)) {
			if (velocityComponent->parent->GetComponent<TransformComponent>()) {
				if (velocityComponent->_velocity._x != 0.0f || velocityComponent->_velocity._y != 0.0f) {
					velocityComponent->parent->GetComponent<TransformComponent>()->_position += velocityComponent->_velocity;
				}
			}
		}
	}
}


void TransformSystem::AddComponentReference(VelocityComponent* velocityComponent)
{
	ISystem::AddComponentReference(velocityComponent);
}
