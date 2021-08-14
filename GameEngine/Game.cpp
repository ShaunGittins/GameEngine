#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

SDL_Rect rect;

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	_running = true;
	Init();
	cout << "Game initialized" << endl;
}

Game::~Game() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	cout << "Game terminated" << endl;
}

void Game::Init()
{
	rect.x = 250;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;
}

void Game::Input() {
	SDL_PollEvent(&_event);
	if (_event.type == SDL_KEYDOWN) {
		switch (_event.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE: _running = false; break;
			case SDL_SCANCODE_Q: rect.x += 1; break;
			default: break;
		}
	}
}

void Game::Update() {
	
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &rect);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}