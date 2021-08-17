#pragma once
#include "IComponent.h"
#include <string>

class NameComponent : public IComponent
{
public:
	NameComponent(std::string name);

	std::string _name;

	void PrintNameToConsole();
};

