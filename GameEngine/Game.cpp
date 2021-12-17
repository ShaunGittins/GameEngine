#include "Game.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "Math.h"

#include "IComponent.h"
#include "NameComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "CameraComponent.h"

#include <iostream>
#include <imgui_impl_sdlrenderer.h>
#include <imgui_impl_sdl.h>
using namespace std;

using namespace Math;

// IMGUI Testing
Entity* selectedEntity = nullptr;

using std::string;
using std::cout;
using std::endl;

const float PLAYER_MOVEMENT_SPEED = 0.5f;
const float CAMERA_MOVEMENT_SPEED = 0.3f;

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

Game::Game(SDL_Window* window, SDL_Renderer* renderer) {
	_window = window;
	_renderer = renderer;

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_sceneManager = new SceneManager();

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
	CameraComponent* camera1 = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });
	CameraComponent* camera2 = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });
	
	// Scenes:
	// 1. Default
	Scene* defaultScene = new Scene(_renderer, camera1);
	defaultScene->AddEntitiesFromJSON("defaultScene.json");
	_sceneManager->AddScene(defaultScene);

	// 2. Testing
	Scene* testingScene = new Scene(_renderer, camera2);
	testingScene->AddEntitiesFromJSON("testingScene.json");
	_sceneManager->AddScene(testingScene);
}

void Game::Input() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	SDL_PollEvent(&_event);

	if (_event.type == SDL_KEYDOWN || _event.type == SDL_KEYUP) {
		Scene* currentScene = _sceneManager->GetCurrentScene();
		if (currentScene == _sceneManager->GetScene(1)) {
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
		}

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
			running = false;
		}
	}

	if (_event.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&xMouse, &yMouse);
	}

	ImGui_ImplSDL2_ProcessEvent(&_event);
}

void Game::Update(Uint32 deltaTime) {
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame(_window);
	ImGui::NewFrame();

	Scene* currentScene = _sceneManager->GetCurrentScene();
	
	if (currentScene == _sceneManager->GetScene(1)) {
		ImGui::Begin("General");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

		ImGui::Begin("Entities");

		if (ImGui::ListBoxHeader("Entities"))
		{
			for (Entity* entity : currentScene->entities)
			{
				string item_name = to_string(entity->_id);
				if (entity->GetComponent<NameComponent>()) {
					item_name += " \"" + entity->GetComponent<NameComponent>()->_name + "\"";
				}
				bool is_selected = selectedEntity == entity;
				if (ImGui::Selectable(item_name.c_str(), is_selected))
				{
					selectedEntity = entity;
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::ListBoxFooter();
		}

		ImGui::End();

		ImGui::ShowDemoWindow();

		if (selectedEntity != nullptr) {
			ImGui::Begin("Entity properties");

			string guiSelectedIdentifier = "id: " + to_string(selectedEntity->_id);

			if (selectedEntity->GetComponent<NameComponent>()) {
				guiSelectedIdentifier += " | name: \"" + selectedEntity->GetComponent<NameComponent>()->_name + "\"";
			}

			ImGui::Text(guiSelectedIdentifier.c_str());

			if (selectedEntity->GetComponent<RenderComponent>()) {
				ImGui::Text("Render Component:");
				ImGui::Checkbox("Visible", &selectedEntity->GetComponent<RenderComponent>()->isVisible);
				ImGui::SliderInt("Layer", &selectedEntity->GetComponent<RenderComponent>()->layer, 0, 10);
			}

			if (selectedEntity->GetComponent<TransformComponent>()) {
				TransformComponent* selectedTransformComponent = selectedEntity->GetComponent<TransformComponent>();

				ImGui::Text("Transform Component:");
				static float position[2] = { selectedTransformComponent->_position._x, selectedTransformComponent->_position._y };
				ImGui::DragFloat2("position", position);
				selectedTransformComponent->_position = Vector2(position[0], position[1]);

				ImGui::DragFloat("rotation", &selectedTransformComponent->_rotation, 1.0f, 0.0f, 360.0f);

				static float scale[2] = { selectedTransformComponent->_scale._x, selectedTransformComponent->_scale._y };
				ImGui::DragFloat2("scale", scale);
				selectedTransformComponent->_scale = Vector2(scale[0], scale[1]);
			}

			ImGui::End();
		}

		Vector2 movementVec = Vector2(0.0f, 0.0f);

		if (controlInput.left) movementVec += Vector2(-PLAYER_MOVEMENT_SPEED, 0) * deltaTime;
		if (controlInput.right) movementVec += Vector2(PLAYER_MOVEMENT_SPEED, 0) * deltaTime;
		if (controlInput.up) movementVec += Vector2(0, -PLAYER_MOVEMENT_SPEED) * deltaTime;
		if (controlInput.down) movementVec += Vector2(0, PLAYER_MOVEMENT_SPEED) * deltaTime;

		// TODO: Make camera an entity with a transform and velocity component instead of putting code here
		CameraComponent* cam = currentScene->GetMainCamera();
		Vector2 cameraVelocity = { 0.0f, 0.0f };

		if (Entity* player = currentScene->GetEntityByName("Player")) {
			// Player velocity
			player->GetComponent<VelocityComponent>()->_velocity = movementVec;

			// Player rotation
			Vector2 mouseWorldPos = currentScene->CameraToWorldPosition({ static_cast<float>(xMouse), static_cast<float>(yMouse) });
			TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
			playerTransform->_rotation = Math::angleTo(player->GetComponent<TransformComponent>()->_position, mouseWorldPos);

			// Camera follow player
			Vector2 cameraPos = { cam->_cameraRect.x + (cam->_cameraRect.w / 2), cam->_cameraRect.y + (cam->_cameraRect.h / 2) };
			if (Math::distance(cameraPos, playerTransform->_position) > 30) {
				cameraVelocity = Math::velocityTo(cameraPos, playerTransform->_position);
			}
		}

		cam->_cameraRect.x += cameraVelocity._x * CAMERA_MOVEMENT_SPEED * deltaTime;
		cam->_cameraRect.y += cameraVelocity._y * CAMERA_MOVEMENT_SPEED * deltaTime;
	}

	currentScene->Update();
}

void Game::Render() {
	ImGui::Render();
	SDL_RenderClear(_renderer);
	_sceneManager->GetCurrentScene()->Render();
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(_renderer);
}