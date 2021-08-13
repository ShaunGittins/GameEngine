#pragma once
#include "SDL.h"

class Game
{
public:
	Game(SDL_Window* window);
	~Game();

	bool _running;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
};

