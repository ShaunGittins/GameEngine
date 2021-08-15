#pragma once

class Entity;

class IComponent
{
public:
	IComponent();
	IComponent(const IComponent& source);
	virtual ~IComponent() {};

	Entity* parent;
};

