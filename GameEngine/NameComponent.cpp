#include "NameComponent.h"
#include <iostream>

NameComponent::NameComponent(std::string name)
{
	_name = name;
}

void NameComponent::PrintNameToConsole()
{
	std::cout << "Entity name: " + _name << std::endl;
}
