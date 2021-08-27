#pragma once
#include "IComponent.h"
#include "Vector2.h"

class RectColliderComponent : public IComponent
{
public:
	RectColliderComponent(Vector2 size, Vector2 offset, bool isCollider);

	Vector2 _size;
	Vector2 _offset;

	// Specifies whether the entity this is attached to is the collision-maker or the entity of the other collider component
	bool _isCollider;
};

