#pragma once
#include <cstdint>
#include <vector>
#include "IComponent.h"

class Entity
{
public:
	uint64_t _id;
	Entity() { static uint64_t counter = 0; _id = counter++; }
	virtual ~Entity();

	void AddComponent(IComponent* component);

	template<class T>
	T* GetComponent();

private:
	std::vector<IComponent*> _components;
};

template<class T>
inline T* Entity::GetComponent()
{
	for (auto& component : _components) {
		T* ptr = dynamic_cast<T*>(component);
		if (ptr) return ptr;
	}
	return nullptr;
}
