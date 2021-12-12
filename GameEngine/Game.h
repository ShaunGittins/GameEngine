#pragma once
#include "SDL.h"
#include "SceneManager.h"
#include <Vector>

class Game
{
public:
	Game();
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

	bool _running;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Event _event;

	SceneManager* _sceneManager;

	void Init();
};

