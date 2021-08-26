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

	/**
	* Add a component to this entity.
	*
	* @param component the component to add
	*/
	void AddComponent(IComponent* component);

	/**
	* Get a component from this entity.
	*
	* @param component the type of component to get
	* @return pointer to accessed component, or NULL if not attached component of type found
	*/
	template<class T>
	T* GetComponent();

	int layer = 0;
	bool operator< (const Entity& other) const;

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
