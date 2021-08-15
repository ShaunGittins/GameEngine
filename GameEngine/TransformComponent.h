#pragma once
#include "IComponent.h"
#include "Vector2.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(Vector2 position, float rotation, Vector2 scale);

	Vector2 _position;
	float _rotation;
	Vector2 _scale;
};

