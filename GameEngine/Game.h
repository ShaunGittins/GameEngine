#pragma once
#include <SDL.h>
#include "SceneManager.h"

class GameEngine;

class Game
{
public:
	Game(SceneManager* sceneManager) {
		_sceneManager = sceneManager;
	}

	void Start();

	void End();

	void Input(SDL_Event event);

	void Update(Uint32 deltaTime);

	void Render(SDL_Renderer* renderer);

private:
	SceneManager* _sceneManager;
};

