#pragma once
#include "SDL.h"
#include "RenderSystem.h"

class Game
{
public:
	Game(SDL_Window* window);
	~Game();

	void Input();
	void Update(Uint32 delta_time);
	void Render();

	bool _running;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;

	RenderSystem* _renderSystem;

	void Init();
};

