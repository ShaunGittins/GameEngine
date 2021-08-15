#include "Name.h"
#include <iostream>

Name::Name(std::string name)
{
	_name = name;
}

void Name::PrintNameToConsole()
{
	std::cout << "Name of entity that is component is attached to: " + _name << std::endl;
}
