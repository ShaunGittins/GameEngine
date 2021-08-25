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

	_running = true;
	Init();
}

Game::~Game() {
	delete _sceneManager;

	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Game::Init()
{
	// Simple "background" entity example
	Entity* background = new Entity();
	RenderComponent* backgroundRenderComponent = new RenderComponent(_renderer);
	backgroundRenderComponent->AddSprite(SDL_LoadBMP("Background.bmp"), { 0, 0, 928, 793 });
	background->AddComponent(backgroundRenderComponent);

	// Simple "player" entity example
	Entity* player = new Entity();
	player->AddComponent(new NameComponent("Player"));

	RenderComponent* playerRenderComponent = new RenderComponent(_renderer);
	playerRenderComponent->AddRect({ 4, 4, 15, 8 });
	playerRenderComponent->AddRect({ 8, 8, 12, 12 });
	playerRenderComponent->AddSprite(SDL_LoadBMP("ball.bmp"), { 32, 32, 32, 48 });
	player->AddComponent(playerRenderComponent);

	player->AddComponent(new TransformComponent({ 250, 150 }, 0.0f, { 48, 48 }));
	player->AddComponent(new VelocityComponent(Vector2(0, 0)));

	// Camera to attach to scene/s
	int w, h;
	SDL_GetRendererOutputSize(_renderer, &w, &h);
	CameraComponent* defaultCamera = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });

	
	// Create a populate scenes
	_sceneManager->AddScene(new Scene(_renderer, defaultCamera));
	_sceneManager->GetCurrentScene()->AddEntityToScene(background);
	_sceneManager->GetCurrentScene()->AddEntityToScene(player);

	// TODO: Determine what to do if entity with main camera component does not exist in current scene
	_sceneManager->AddScene(new Scene(_renderer, defaultCamera));
	_sceneManager->GetScene(1)->AddEntityToScene(background);
}

void Game::Input() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	SDL_PollEvent(&_event);

	if (_event.type == SDL_KEYDOWN || _event.type == SDL_KEYUP) {
		// Player movement
		controlInput.up = (keyboard_state[SDL_SCANCODE_W] && !(keyboard_state[SDL_SCANCODE_S]));
		controlInput.down = (!keyboard_state[SDL_SCANCODE_W] && (keyboard_state[SDL_SCANCODE_S]));
		controlInput.left = (keyboard_state[SDL_SCANCODE_A] && !(keyboard_state[SDL_SCANCODE_D]));
		controlInput.right = (!keyboard_state[SDL_SCANCODE_A] && (keyboard_state[SDL_SCANCODE_D]));
		
		// Camera movement
		cameraControlInput.up = (keyboard_state[SDL_SCANCODE_UP] && !(keyboard_state[SDL_SCANCODE_DOWN]));
		cameraControlInput.down = (!keyboard_state[SDL_SCANCODE_UP] && (keyboard_state[SDL_SCANCODE_DOWN]));
		cameraControlInput.left = (keyboard_state[SDL_SCANCODE_LEFT] && !(keyboard_state[SDL_SCANCODE_RIGHT]));
		cameraControlInput.right = (!keyboard_state[SDL_SCANCODE_LEFT] && (keyboard_state[SDL_SCANCODE_RIGHT]));

		// Switch scenes
		if (keyboard_state[SDL_SCANCODE_Y]) {
			if (_sceneManager->GetCurrentSceneNumber() == 0) {
				_sceneManager->SetScene(1);
			}
			else {
				_sceneManager->SetScene(0);
			}
		}

		// Quit
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

	Scene* currentScene = _sceneManager->GetCurrentScene();

	if (Entity* player = currentScene->GetEntityByName("Player")) {
		player->GetComponent<VelocityComponent>()->_velocity = movementVec;
	}

	if (cameraControlInput.left) currentScene->GetMainCamera()->_cameraRect.x -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.right) currentScene->GetMainCamera()->_cameraRect.x += MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.up) currentScene->GetMainCamera()->_cameraRect.y -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.down) currentScene->GetMainCamera()->_cameraRect.y += MOVEMENT_SPEED * deltaTime;

	currentScene->Update();
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	_sceneManager->GetCurrentScene()->Render();

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}