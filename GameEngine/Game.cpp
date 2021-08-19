#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "NameComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "IComponent.h"
#include "RenderSystem.h"

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
NameComponent* myNameComponent;
RenderComponent* myRenderComponent;
TransformComponent* myTransformComponent;

SDL_Surface* ballBitmapSurface = NULL;

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_renderSystem = new RenderSystem(_renderer);

	_running = true;
	Init();
}

Game::~Game() {
	delete myEntity;
	delete _renderSystem;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Game::Init()
{
	myEntity = new Entity();
	cout << myEntity->_id << endl;

	myEntity->AddComponent(new NameComponent("Steve"));

	if (myEntity->GetComponent<NameComponent>()) {
		myEntity->GetComponent<NameComponent>()->PrintNameToConsole();
	}

	RenderComponent* myEntityRenderComponent = new RenderComponent(_renderer);
	SDL_Rect mySpriteRect{ 4, 4, 15, 8 };
	SDL_Rect mySpriteRect2{ 8, 8, 12, 12 };
	myEntityRenderComponent->AddRect(mySpriteRect);
	myEntityRenderComponent->AddRect(mySpriteRect2);
	myEntityRenderComponent->AddSprite(SDL_LoadBMP("ball.bmp"), mySpriteRect);
	myEntity->AddComponent(myEntityRenderComponent);

	Vector2 myInitPos = Vector2(250, 150);
	Vector2 myInitScale = Vector2(48, 48);
	myEntity->AddComponent(new TransformComponent(myInitPos, 0.0f, myInitScale));

	_renderSystem->AddComponentReference(myEntityRenderComponent);
}

void Game::Input() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	SDL_PollEvent(&_event);

	if (_event.type == SDL_KEYDOWN || _event.type == SDL_KEYUP) {
		controlInput.up = (keyboard_state[SDL_SCANCODE_W] && !(keyboard_state[SDL_SCANCODE_S]));
		controlInput.down = (!keyboard_state[SDL_SCANCODE_W] && (keyboard_state[SDL_SCANCODE_S]));
		controlInput.left = (keyboard_state[SDL_SCANCODE_A] && !(keyboard_state[SDL_SCANCODE_D]));
		controlInput.right = (!keyboard_state[SDL_SCANCODE_A] && (keyboard_state[SDL_SCANCODE_D]));
		if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
			_running = false;
		}
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
	
	_renderSystem->Render();

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}