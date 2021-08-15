#pragma once
#include "IComponent.h"

class TransformComponent : public IComponent
{
public:
	TransformComponent(int posX, int posY, int rotation, int width, int height);

	// TODO: Create Vector2 object for TransformComponent to use
	int _posX;
	int _posY;
	int _rotation;
	int _width;
	int _height;
};

