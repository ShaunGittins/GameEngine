#include <iostream>
#include <SDL.h>
#include "Game.h"

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	Game* game = new Game(window);

	while (game->_running) {
		game->Input();
		game->Update();
		game->Render();
	}

	delete game;
	return 0;
}