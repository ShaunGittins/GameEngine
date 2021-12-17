#pragma once
#include "IComponent.h"
#include "Sprite.h"
#include <vector>
#include <SDL.h>
#include "Vector2.h"
#include <string>

class RenderComponent : public IComponent
{
public:
	RenderComponent(SDL_Renderer* renderer);
	RenderComponent(SDL_Renderer* renderer, bool visible);
	~RenderComponent();

	void Render(Vector2 cameraPos);

	void AddSprite(std::string filename, SDL_FRect spriteRect, float originX, float originY, double angle);
	void AddRect(SDL_FRect spriteRect);

	void ToggleVisibility();

	bool isVisible;

	int layer = 0;

	std::vector<SDL_FRect> rects;
	std::vector<Sprite*> sprites;

private:
	SDL_Renderer* _renderer;
};

