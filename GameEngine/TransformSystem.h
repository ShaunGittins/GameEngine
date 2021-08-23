#pragma once
#include "VelocityComponent.h"
#include "ISystem.h"
#include <vector>

class TransformSystem : ISystem
{
public:
	TransformSystem();
	~TransformSystem();

	void Update();

	void AddComponentReference(VelocityComponent* velocityComponent);

private:
	//std::vector<VelocityComponent*> _velocityComponents;
};

