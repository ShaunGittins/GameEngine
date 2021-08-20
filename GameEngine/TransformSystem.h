#pragma once
#include "VelocityComponent.h"
#include <vector>

class TransformSystem
{
public:
	TransformSystem();
	~TransformSystem();

	void Update();

	void AddComponentReference(VelocityComponent* velocityComponent);

private:
	std::vector<VelocityComponent*> _velocityComponents;
};

