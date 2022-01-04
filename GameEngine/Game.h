#pragma once
#include <SDL.h>

class Game
{
public:
	Game() {

	}

	void Start();

	void End();

	void Input();

	void Update(Uint32 deltaTime);

	void Render();
};

