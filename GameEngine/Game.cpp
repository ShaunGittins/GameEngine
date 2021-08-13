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

void Game::Input() {
	SDL_PollEvent(&_event);
	if (_event.type == SDL_KEYDOWN) {
		switch (_event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE: _running = false; break;
			default: break;
		}
	}
}

void Game::Update() {

}

void Game::Render() {

}