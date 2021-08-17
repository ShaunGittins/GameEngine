#include "Name.h"
#include <iostream>

Name::Name(std::string name)
{
	_name = name;
}

void Name::PrintNameToConsole()
{
	std::cout << "Entity name: " + _name << std::endl;
}
