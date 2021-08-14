#pragma once
#include "SDL.h"

class Game
{
public:
	Game(SDL_Window* window);
	~Game();

	void Init();

	void Input();
	void Update();
	void Render();

	bool _running;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;
};

