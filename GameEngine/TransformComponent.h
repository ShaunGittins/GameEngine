#pragma once
#include "IComponent.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(float posX, float posY, float rotation, float width, float height);

	// TODO: Create Vector2 object for TransformComponent to use
	float _posX;
	float _posY;
	float _rotation;
	float _width;
	float _height;
};

