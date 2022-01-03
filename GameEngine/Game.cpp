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

enum class Mode { EDITOR, RUN, RUN_DEBUG };
Mode mode = Mode::EDITOR;

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

	int display_index = SDL_GetWindowDisplayIndex(window);
	SDL_Rect usable_bounds;
	if (0 != SDL_GetDisplayUsableBounds(display_index, &usable_bounds)) {
		SDL_Log("error getting usable bounds");
		return;
	}

	SDL_SetWindowPosition(window, usable_bounds.x, usable_bounds.y);
	SDL_SetWindowSize(window, usable_bounds.w, usable_bounds.h);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	Init();
}

Game::~Game() {
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
	
	// Add scenes:
	sceneManager.AddScene(new Scene(_renderer, camera1), "defaultScene.json");
	sceneManager.AddScene(new Scene(_renderer, camera2), "testingScene.json");
}

void Game::Input() {
	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			Scene* currentScene = sceneManager.GetCurrentScene();
			if (currentScene == sceneManager.GetScene(1)) {
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
				if (sceneManager.GetCurrentSceneNumber() == 0) {
					sceneManager.SetScene(1);
				}
				else {
					sceneManager.SetScene(0);
				}
			}

			// Quit
			if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
				if (mode == Mode::RUN) {
					mode = Mode::EDITOR;
				}
				else if (mode == Mode::EDITOR) {
					running = false;
				}
			}
		}

		if (event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&xMouse, &yMouse);
		}

		if (mode == Mode::EDITOR) {
			ImGui_ImplSDL2_ProcessEvent(&event);
		}
	}

}

void Game::Update(Uint32 deltaTime) {
	Scene* currentScene = sceneManager.GetCurrentScene();

	if (mode == Mode::EDITOR) {
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame(_window);
		ImGui::NewFrame();

		ImGui::Begin("General");
		if (ImGui::ArrowButton("##run", ImGuiDir_Right)) { mode = Mode::RUN; }
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

		ImGui::Begin("Entities");

		if (ImGui::ListBoxHeader("Entities"))
		{
			for (Entity* entity : currentScene->entities)
			{
				string entityName = to_string(entity->_id);
				if (entity->GetComponent<NameComponent>()) {
					entityName += " \"" + entity->GetComponent<NameComponent>()->_name + "\"";
				}
				bool isSelected = selectedEntity == entity;
				if (ImGui::Selectable(entityName.c_str(), isSelected))
				{
					selectedEntity = entity;
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::ListBoxFooter();
		}

		ImGui::End();

		ImGui::ShowDemoWindow();

		if (selectedEntity != nullptr) {
			ImGui::Begin("Entity properties");


			// GUI Component ID / Name
			string guiSelectedIdentifier = "id: " + to_string(selectedEntity->_id);

			if (selectedEntity->GetComponent<NameComponent>()) {
				guiSelectedIdentifier += " | name: \"" + selectedEntity->GetComponent<NameComponent>()->_name + "\"";
			}

			ImGui::Text(guiSelectedIdentifier.c_str());
			ImGui::Separator();
			ImGui::Text("Components:");

			// GUI Component Render
			if (RenderComponent* rc = selectedEntity->GetComponent<RenderComponent>()) {
				if (ImGui::CollapsingHeader("Render Component")) {
					ImGui::Checkbox("Visible", &rc->isVisible);
					ImGui::SliderInt("Layer", &rc->layer, 0, 10);

					if (rc->rects.size() > 0) {
						ImGui::Text("Primitives: ");
					}

					// TODO: Rework so one renderComponent = one sprite or primitive?
					if (rc->sprites.size() > 0) {
						ImGui::Text("Sprite: ");
						Sprite* mySprite = *rc->sprites.begin();
						ImGui::Text(("File name: " + mySprite->filename).c_str());

						static float* position[2] = { &mySprite->rect.x, &mySprite->rect.y };
						ImGui::DragFloat2("Position relative", *(position));

						static float* scale[2] = { &mySprite->rect.w, &mySprite->rect.h };
						ImGui::DragFloat2("Size", *(scale));

						static float* pivot[2] = { &mySprite->rotationPoint.x, &mySprite->rotationPoint.y };
						ImGui::DragFloat2("Pivot point", *(pivot));

						ImGui::SliderFloat("Angle", &mySprite->angle, -360, 360, "%.0f deg", ImGuiSliderFlags_None);
						ImGui::Text(to_string(mySprite->angle).c_str());
					}
				}
			}

			// GUI Component Transform
			if (TransformComponent* tc = selectedEntity->GetComponent<TransformComponent>()) {
				if (ImGui::CollapsingHeader("Transform Component")) {
					ImGui::Text("Transform Component:");
					static float* position[2] = { &tc->_position._x, &tc->_position._y };
					ImGui::DragFloat2("position", *(position));

					ImGui::DragFloat("rotation", &tc->_rotation, 1.0f, 0.0f, 360.0f);

					static float* scale[2] = { &tc->_scale._x, &tc->_scale._y };
					ImGui::DragFloat2("scale", *(scale));
				}
			}

			ImGui::End();
		}
	}

	if (currentScene == sceneManager.GetScene(1)) {
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
	sceneManager.GetCurrentScene()->Render();
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	if (mode == Mode::EDITOR) {
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	}

	SDL_RenderPresent(_renderer);
}