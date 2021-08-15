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

Entity* myEntity;
Name* myNameComponent;
RenderComponent* myRenderComponent;
TransformComponent* myTransformComponent;

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	_running = true;
	Init();
	cout << "Game initialized" << endl;
}

Game::~Game() {
	delete myEntity;
	delete myNameComponent;
	delete myRenderComponent;
	delete myTransformComponent;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
	cout << "Game terminated" << endl;
}

void Game::Init()
{
	myEntity = new Entity();
	cout << myEntity->_id << endl;

	myNameComponent = new Name("Steve");
	myEntity->AddComponent(myNameComponent);

	myRenderComponent = new RenderComponent();
	myEntity->AddComponent(myRenderComponent);

	// TODO: ScaleX and ScaleY instead of width and height, not everything will be a rect
	Vector2 myInitPos = Vector2(250, 150);
	Vector2 myInitScale = Vector2(48, 48);
	myTransformComponent = new TransformComponent(myInitPos, 0.0f, myInitScale);
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
		tc->_position._x -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.right) {
		tc->_position._x += MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.up) {
		tc->_position._y -= MOVEMENT_SPEED * delta_time;
	}
	if (controlInput.down) {
		tc->_position._y += MOVEMENT_SPEED * delta_time;
	}
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	if (myEntity->GetComponent<TransformComponent>() && myEntity->GetComponent<RenderComponent>()) {
		if (myEntity->GetComponent<RenderComponent>()->isVisible) {
			TransformComponent* tc = myEntity->GetComponent<TransformComponent>();
			SDL_FRect rect;
			rect.x = tc->_position._x;
			rect.y = tc->_position._y;
			rect.w = tc->_scale._x;
			rect.h = tc->_scale._y;

			SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
			SDL_RenderFillRectF(_renderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}