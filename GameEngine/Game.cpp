#include "Game.h"
#include <iostream>
#include "Entity.h"
#include "NameComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "IComponent.h"
#include "RenderSystem.h"
#include "CameraComponent.h"
#include "SceneManager.h"

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
ControlInput cameraControlInput;

NameComponent* myNameComponent;
RenderComponent* myRenderComponent;
TransformComponent* myTransformComponent;

SDL_Surface* ballBitmapSurface = NULL;

SDL_FRect defaultCameraRect { 0, 0, 928, 793 };
CameraComponent* defaultCamera = new CameraComponent(defaultCameraRect);

Game::Game(SDL_Window* window) {
	_window = window;
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_sceneManager = new SceneManager();

	_renderSystem = new RenderSystem(_renderer, defaultCamera);
	_transformSystem = new TransformSystem();

	_running = true;
	Init();
}

Game::~Game() {
	delete _sceneManager;
	delete _renderSystem;
	delete _transformSystem;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Game::Init()
{
	_sceneManager->AddScene(Scene());

	Entity* bgEntity = new Entity();
	RenderComponent* bgRenderComponent = new RenderComponent(_renderer);
	SDL_FRect sceneRect{ 0, 0, 928, 793 };
	bgRenderComponent->AddSprite(SDL_LoadBMP("Background.bmp"), sceneRect);
	bgEntity->AddComponent(bgRenderComponent);
	_renderSystem->AddComponentReference(bgRenderComponent);

	Entity*myEntity = new Entity();

	myEntity->AddComponent(new NameComponent("Player"));

	if (myEntity->GetComponent<NameComponent>()) {
		myEntity->GetComponent<NameComponent>()->PrintNameToConsole();
	}

	RenderComponent* myEntityRenderComponent = new RenderComponent(_renderer);
	SDL_FRect myRect{ 4, 4, 15, 8 };
	SDL_FRect myRect2{ 8, 8, 12, 12 };
	SDL_FRect mySpriteRect{ 32, 32, 32, 48 };
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

	int w, h;
	SDL_GetRendererOutputSize(_renderer, &w, &h);
	myEntity->AddComponent(new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) }));

	_renderSystem->SetMainCamera(myEntity->GetComponent<CameraComponent>());

	_sceneManager->GetCurrentScene()->AddEntityToScene(bgEntity);
	_sceneManager->GetCurrentScene()->AddEntityToScene(myEntity);
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
		cameraControlInput.up = (keyboard_state[SDL_SCANCODE_UP] && !(keyboard_state[SDL_SCANCODE_DOWN]));
		cameraControlInput.down = (!keyboard_state[SDL_SCANCODE_UP] && (keyboard_state[SDL_SCANCODE_DOWN]));
		cameraControlInput.left = (keyboard_state[SDL_SCANCODE_LEFT] && !(keyboard_state[SDL_SCANCODE_RIGHT]));
		cameraControlInput.right = (!keyboard_state[SDL_SCANCODE_LEFT] && (keyboard_state[SDL_SCANCODE_RIGHT]));
	}
}

void Game::Update(Uint32 deltaTime) {
	Vector2 movementVec = Vector2(0.0f, 0.0f);

	if (controlInput.left) movementVec += Vector2(-MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.right) movementVec += Vector2(MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.up) movementVec += Vector2(0, -MOVEMENT_SPEED) * deltaTime;
	if (controlInput.down) movementVec += Vector2(0, MOVEMENT_SPEED) * deltaTime;

	_sceneManager->GetCurrentScene()->GetEntityByName("Player")->GetComponent<VelocityComponent>()->_velocity = movementVec;

	if (cameraControlInput.left) _renderSystem->GetMainCamera()->_cameraRect.x -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.right) _renderSystem->GetMainCamera()->_cameraRect.x += MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.up) _renderSystem->GetMainCamera()->_cameraRect.y -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.down) _renderSystem->GetMainCamera()->_cameraRect.y += MOVEMENT_SPEED * deltaTime;

	_transformSystem->Update();
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	_renderSystem->Render();

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}