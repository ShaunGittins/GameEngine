#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	_running = true;
	cout << "Game initialized" << endl;
}

Game::~Game() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	cout << "Game terminated" << endl;
}