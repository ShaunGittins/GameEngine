#pragma once
#include "IComponent.h"
#include "Vector2.h"

class VelocityComponent : public IComponent
{
public:
	VelocityComponent();
	VelocityComponent(Vector2 velocity);

	Vector2 _velocity;
};

