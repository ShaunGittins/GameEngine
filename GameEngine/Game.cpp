#include "Game.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "Math.h"
using namespace Math;

#include "IComponent.h"
#include "NameComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "CameraComponent.h"

#include <iostream>

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace rapidjson;

using std::string;
using std::cout;
using std::endl;

const float MOVEMENT_SPEED = 0.5f;

int xMouse = 0, yMouse = 0;
class ControlInput {
public:
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

ControlInput controlInput;
ControlInput cameraControlInput;

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
	// Camera to attach to scene/s
	int w, h;
	SDL_GetRendererOutputSize(_renderer, &w, &h);
	CameraComponent* defaultCamera = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });

	
	// Create a populate scenes
	_sceneManager->AddScene(new Scene(_renderer, defaultCamera));
	LoadEntitiesFromJSON("game.json");
}

void Game::LoadEntitiesFromJSON(std::string filename)
{
	// Load JSON file to document
	std::ifstream ifs(filename);
	IStreamWrapper isw(ifs);
	Document document;
	document.ParseStream(isw);

	// Load document to entities
	assert(document.HasMember("entities"));
	const Value& entities = document["entities"];
	assert(entities.IsArray());

	for (SizeType i = 0; i < entities.Size(); i++) {
		Entity* entity = new Entity();
		const Value& components = entities[i]["components"];

		if (components.HasMember("name")) {
			string name = components["name"].GetString();
			entity->AddComponent(new NameComponent(name));
		}

		if (components.HasMember("render")) {
			RenderComponent* renderComponent = new RenderComponent(_renderer);
			renderComponent->layer = components["render"]["layer"].GetInt();

			if (components["render"].HasMember("rectangles")) {
				const Value& rectangles = components["render"]["rectangles"];
				for (SizeType j = 0; j < rectangles.Size(); j++) {
					float x = rectangles[j]["x"].GetFloat();
					float y = rectangles[j]["y"].GetFloat();
					float width = rectangles[j]["width"].GetFloat();
					float height = rectangles[j]["height"].GetFloat();
					renderComponent->AddRect({ x, y, width, height });
				}
			}

			if (components["render"].HasMember("sprites")) {
				const Value& sprites = components["render"]["sprites"];
				for (SizeType j = 0; j < sprites.Size(); j++) {
					float x = sprites[j]["x"].GetFloat();
					float y = sprites[j]["y"].GetFloat();
					float width = sprites[j]["width"].GetFloat();
					float height = sprites[j]["height"].GetFloat();
					string filename = sprites[j]["filename"].GetString();
					float originX = 0.0f;
					float originY = 0.0f;
					double angle = 0;
					if (sprites[j].HasMember("originX") && sprites[j].HasMember("originY") && sprites[j].HasMember("angle")) {
						originX = sprites[j]["originX"].GetFloat();
						originY = sprites[j]["originY"].GetFloat();
						angle = sprites[j]["angle"].GetDouble();
					}
					renderComponent->AddSprite(SDL_LoadBMP(filename.c_str()), { x, y, width, height }, originX, originY, angle);
				}
			}
			
			entity->AddComponent(renderComponent);
		}

		if (components.HasMember("transform")) {
			float x = components["transform"]["xPosition"].GetFloat();
			float y = components["transform"]["yPosition"].GetFloat();
			float rotation = components["transform"]["rotation"].GetFloat();
			float xScale = components["transform"]["xScale"].GetFloat();
			float yScale = components["transform"]["yScale"].GetFloat();
			entity->AddComponent(new TransformComponent({ x, y }, rotation, { xScale, yScale }));
		}

		if (components.HasMember("velocity")) {
			float x = components["velocity"]["x"].GetFloat();
			float y = components["velocity"]["y"].GetFloat();
			entity->AddComponent(new VelocityComponent(Vector2(x, y)));
		}

		_sceneManager->GetCurrentScene()->AddEntityToScene(entity);
	}
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
		/*
		if (keyboard_state[SDL_SCANCODE_Y]) {
			if (_sceneManager->GetCurrentSceneNumber() == 0) {
				_sceneManager->SetScene(1);
			}
			else {
				_sceneManager->SetScene(0);
			}
		}
		*/

		// Quit
		if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
			_running = false;
		}
	}

	if (_event.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&xMouse, &yMouse);
	}
}

double rot = 0.0f;

void Game::Update(Uint32 deltaTime) {
	Vector2 movementVec = Vector2(0.0f, 0.0f);

	if (controlInput.left) movementVec += Vector2(-MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.right) movementVec += Vector2(MOVEMENT_SPEED, 0) * deltaTime;
	if (controlInput.up) movementVec += Vector2(0, -MOVEMENT_SPEED) * deltaTime;
	if (controlInput.down) movementVec += Vector2(0, MOVEMENT_SPEED) * deltaTime;

	Scene* currentScene = _sceneManager->GetCurrentScene();

	if (Entity* player = currentScene->GetEntityByName("Player")) {
		player->GetComponent<VelocityComponent>()->_velocity = movementVec;
		rot = Math::angleTo(player->GetComponent<TransformComponent>()->_position, { static_cast<float>(xMouse), static_cast<float>(yMouse) });
		player->GetComponent<TransformComponent>()->_rotation = rot;
	}

	if (cameraControlInput.left) currentScene->GetMainCamera()->_cameraRect.x -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.right) currentScene->GetMainCamera()->_cameraRect.x += MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.up) currentScene->GetMainCamera()->_cameraRect.y -= MOVEMENT_SPEED * deltaTime;
	if (cameraControlInput.down) currentScene->GetMainCamera()->_cameraRect.y += MOVEMENT_SPEED * deltaTime;

	currentScene->Update();
}

void Game::Render() {
	SDL_RenderClear(_renderer);

	cout << "Angle: " << rot << endl;
	_sceneManager->GetCurrentScene()->Render();

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderPresent(_renderer);
}