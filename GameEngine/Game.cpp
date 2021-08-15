#include "Game.h"
#include <iostream>
#include "Entity.h"

using std::cout;
using std::endl;

const float MOVEMENT_SPEED = 1;
SDL_Rect rect;

class ControlInput {
public:
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

ControlInput controlInput;

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
	Entity* myEntity = new Entity();
	cout << myEntity->_id << endl;

	rect.x = 250;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;
}

void Game::Input() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	SDL_PollEvent(&_event);

	if (_event.type == SDL_KEYDOWN || _event.type == SDL_KEYUP) {
		controlInput.up = (keyboard_state[SDL_SCANCODE_W] && !(keyboard_state[SDL_SCANCODE_S]));
		controlInput.down = (!keyboard_state[SDL_SCANCODE_W] && (keyboard_state[SDL_SCANCODE_S]));
		controlInput.left = (keyboard_state[SDL_SCANCODE_A] && !(keyboard_state[SDL_SCANCODE_D]));
		controlInput.right = (!keyboard_state[SDL_SCANCODE_A] && (keyboard_state[SDL_SCANCODE_D]));
	}
}

void Game::Update(Uint32 delta_time) {
	if (controlInput.left) {
		rect.x -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.right) {
		rect.x += MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.up) {
		rect.y -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.down) {
		rect.y += MOVEMENT_SPEED * delta_time;
	}
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &rect);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}