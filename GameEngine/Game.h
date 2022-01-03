#pragma once
#include "SDL.h"
#include "SceneManager.h"
#include <Vector>

class Game
{
public:
	Game(SDL_Window* SDL_window, SDL_Renderer* renderer);
	~Game();

	/**
	* Process input from devices (e.g. keyboard)
	*/
	void Input();

	/**
	* Update the game
	*
	* @param deltaTime time since last update loop
	*/
	void Update(Uint32 deltaTime);

	/**
	* Draw everything visible to the screen
	*/
	void Render();

	bool running = true;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SceneManager sceneManager = SceneManager();

	void Init();
};

