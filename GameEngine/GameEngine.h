#pragma once
#include "SDL.h"
#include "SceneManager.h"
#include "Mode.h"
#include "Game.h"
#include <Vector>

class GameEngine
{
public:
	GameEngine(SDL_Window* SDL_window, SDL_Renderer* renderer);
	~GameEngine();

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
	Mode mode = Mode::EDIT;

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	Game _game;
	SceneManager sceneManager = SceneManager();

	void Init();
};

