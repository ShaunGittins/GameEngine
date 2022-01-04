#pragma once
#include <SDL.h>

class GameEngine;

class Game
{
public:
	Game(GameEngine* gameEngine) {
		_gameEngine = gameEngine;
	}

	void Start();

	void End();

	void Input(SDL_Event event);

	void Update(Uint32 deltaTime);

	void Render(SDL_Renderer* renderer);

private:
	GameEngine* _gameEngine;
};

