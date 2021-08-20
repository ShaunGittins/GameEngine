#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "NameComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
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
Entity* danielEntity;
NameComponent* myNameComponent;
RenderComponent* myRenderComponent;
TransformComponent* myTransformComponent;

SDL_Surface* ballBitmapSurface = NULL;

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_renderSystem = new RenderSystem(_renderer);
	_transformSystem = new TransformSystem();

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

	myEntity->AddComponent(new NameComponent("Steve"));

	if (myEntity->GetComponent<NameComponent>()) {
		myEntity->GetComponent<NameComponent>()->PrintNameToConsole();
	}

	RenderComponent* myEntityRenderComponent = new RenderComponent(_renderer);
	SDL_Rect myRect{ 4, 4, 15, 8 };
	SDL_Rect myRect2{ 8, 8, 12, 12 };
	SDL_Rect mySpriteRect{ 32, 32, 32, 48 };
	myEntityRenderComponent->AddRect(myRect);
	myEntityRenderComponent->AddRect(myRect2);
	myEntityRenderComponent->AddSprite(SDL_LoadBMP("ball.bmp"), mySpriteRect);
	myEntity->AddComponent(myEntityRenderComponent);

	Vector2 myInitPos = Vector2(250, 150);
	Vector2 myInitScale = Vector2(48, 48);
	myEntity->AddComponent(new TransformComponent(myInitPos, 0.0f, myInitScale));
	VelocityComponent* myVelocityComponent = new VelocityComponent(Vector2(0, 0));
	myEntity->AddComponent(myVelocityComponent);

	_renderSystem->AddComponentReference(myEntityRenderComponent);
	_transformSystem->AddComponentReference(myVelocityComponent);

	danielEntity = new Entity();
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

void Game::Update(Uint32 deltaTime) {
	Vector2 movementVec = Vector2(0.0f, 0.0f);

	if (controlInput.left) movementVec += Vector2(-MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.right) movementVec += Vector2(MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.up) movementVec += Vector2(0, -MOVEMENT_SPEED) * deltaTime;
	if (controlInput.down) movementVec += Vector2(0, MOVEMENT_SPEED) * deltaTime;

	myEntity->GetComponent<VelocityComponent>()->_velocity = movementVec;

	_transformSystem->Update();
}

void Game::Render() {
	SDL_RenderClear(_renderer);
	
	_renderSystem->Render();

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}