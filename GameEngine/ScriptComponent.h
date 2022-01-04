#pragma once
#include "IComponent.h"
#include <string>

class ScriptComponent : public IComponent
{
public:
	std::string name;

	virtual void Initialize() {};

	virtual void Update() {};

	virtual void Terminate() {};
};

