#include "RectColliderComponent.h"

RectColliderComponent::RectColliderComponent(Vector2 size, Vector2 offset, bool isCollider)
{
	_size = size;
	_offset = offset;
	_isCollider = isCollider;
}
