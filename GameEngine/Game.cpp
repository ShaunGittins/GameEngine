#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "Name.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "IComponent.h"

using std::cout;
using std::endl;

const float MOVEMENT_SPEED = 0.5f;

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

Entity* myEntity;

void Game::Init()
{
	myEntity = new Entity();
	cout << myEntity->_id << endl;

	Name* myNameComponent = new Name("Steve");
	myEntity->AddComponent(myNameComponent);

	RenderComponent* myRenderComponent = new RenderComponent();
	myEntity->AddComponent(myRenderComponent);

	// TODO: ScaleX and ScaleY instead of width and height, not everything will be a rect
	TransformComponent* myTransformComponent = new TransformComponent(250, 150, 0, 200, 200);
	myEntity->AddComponent(myTransformComponent);

	if (myEntity->GetComponent<Name>()) {
		myEntity->GetComponent<Name>()->PrintNameToConsole();
	}
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
	TransformComponent* tc = myEntity->GetComponent<TransformComponent>();
	if (controlInput.left) {
		tc->_posX -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.right) {
		tc->_posX += MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.up) {
		tc->_posY -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.down) {
		tc->_posY += MOVEMENT_SPEED * delta_time;
	}
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	if (myEntity->GetComponent<TransformComponent>() && myEntity->GetComponent<RenderComponent>()) {
		if (myEntity->GetComponent<RenderComponent>()->isVisible) {
			TransformComponent* tc = myEntity->GetComponent<TransformComponent>();
			SDL_FRect rect;
			rect.x = tc->_posX;
			rect.y = tc->_posY;
			rect.w = tc->_width;
			rect.h = tc->_height;

			SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
			SDL_RenderFillRectF(_renderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}