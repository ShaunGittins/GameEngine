#include "GameEngine.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "Entity.h"

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

using std::string;
using std::cout;
using std::endl;


GameEngine::GameEngine(SDL_Window* window, SDL_Renderer* renderer) {
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

	_game.Start();

	Init();
}

GameEngine::~GameEngine() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void GameEngine::Init()
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

void GameEngine::Input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

		if (mode == Mode::RUN || mode == Mode::RUN_DEBUG) {
			_game.Input(event);

			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				if (keyboard_state[SDL_SCANCODE_ESCAPE]) 
					mode = Mode::EDIT;
			}
		}
		else if (mode == Mode::EDIT) {
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				if (keyboard_state[SDL_SCANCODE_LALT] && keyboard_state[SDL_SCANCODE_F4])
					running = false;
			}

			ImGui_ImplSDL2_ProcessEvent(&event);
		}
	}
}

#include "GameGUI.h"

void GameEngine::Update(Uint32 deltaTime) {

	if (mode == Mode::RUN || mode == Mode::RUN_DEBUG) 
		_game.Update(deltaTime);

	Scene* currentScene = sceneManager.GetCurrentScene();

	if (mode == Mode::EDIT) {
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame(_window);
		ImGui::NewFrame();

		GameGUI::ShowEditorMainMenuBar(this);
		GameGUI::ShowEditorGameControlBar(this);
		GameGUI::ShowEditorSceneHierachy(&sceneManager);
		GameGUI::ShowEditorEntityList(currentScene);
		GameGUI::ShowEditorEntityProperties();

		ImGui::ShowDemoWindow();
	}

	currentScene->Update();
}

void GameEngine::Render() {
	ImGui::Render();

	SDL_RenderClear(_renderer);
	sceneManager.GetCurrentScene()->Render();
	_game.Render(_renderer);
	
	if (mode == Mode::EDIT) 
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(_renderer);
}