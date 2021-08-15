#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
	isVisible = true;
}

RenderComponent::RenderComponent(bool visible)
{
	isVisible = visible;
}

void RenderComponent::ToggleVisibility()
{
	isVisible = !isVisible;
}
