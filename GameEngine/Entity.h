#pragma once
#include <cstdint>

class Entity
{
public:
	uint64_t _id;
	Entity() { static uint64_t counter = 0; _id = counter++; }
};

