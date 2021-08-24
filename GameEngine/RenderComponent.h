#pragma once
#include "IComponent.h"
#include "Sprite.h"
#include <vector>
#include <SDL.h>
#include "Vector2.h"

class RenderComponent : public IComponent
{
public:
	RenderComponent(SDL_Renderer* renderer);
	RenderComponent(SDL_Renderer* renderer, bool visible);
	~RenderComponent();

	void Render(Vector2 cameraPos);

	void AddSprite(SDL_Surface* surface, SDL_FRect spriteRect);
	void AddRect(SDL_FRect spriteRect);

	void ToggleVisibility();

	bool isVisible;

private:
	SDL_Renderer* _renderer;
	std::vector<SDL_FRect> _rects;
	std::vector<Sprite*> _sprites;
};

