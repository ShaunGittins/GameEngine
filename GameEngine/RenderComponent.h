#pragma once
#include "IComponent.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent();
	RenderComponent(bool visible);

	void ToggleVisibility();

	bool isVisible;
};

