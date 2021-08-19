#pragma once
#include "IComponent.h"
#include "Sprite.h"
#include <vector>
#include <SDL.h>

class RenderComponent : public IComponent
{
public:
	RenderComponent(SDL_Renderer* renderer);
	RenderComponent(SDL_Renderer* renderer, bool visible);
	~RenderComponent();

	void Render();

	void AddSprite(SDL_Surface* surface, SDL_Rect spriteRect);
	void AddRect(SDL_Rect spriteRect);

	void ToggleVisibility();

	bool isVisible;

private:
	SDL_Renderer* _renderer;
	std::vector<SDL_Rect> _rects;
	std::vector<Sprite*> _sprites;
};

