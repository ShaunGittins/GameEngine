#pragma once
#include "IComponent.h"
#include <string>

class Name : public IComponent
{
public:
	Name(std::string name);

	std::string _name;

	void PrintNameToConsole();
};

