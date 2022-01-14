#include "GameEngine.h"

#include "GameGUI.h"
#include <imgui_impl_sdlrenderer.h>
#include <imgui_impl_sdl.h>

GameEngine::GameEngine(SDL_Window* window, SDL_Renderer* renderer) {
	_window = window;
	_renderer = renderer;

	int display_index = SDL_GetWindowDisplayIndex(window);
	SDL_Rect usable_bounds;
	if (0 != SDL_GetDisplayUsableBounds(display_index, &usable_bounds)) {
		SDL_Log("Unable to get usable display bounds");
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
	int w, h;
	SDL_GetRendererOutputSize(_renderer, &w, &h);

	// TODO: Should each scene have it's own systems? Or should they share systems.
	// It's possible someone may want to extend a system to work uniquely for certain scenes

	CameraComponent* cameraForDefaultScene = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });
	RenderSystem* renderSystemForDefaultScene = new RenderSystem(_renderer, cameraForDefaultScene);
	TransformSystem* transformSystemForDefaultScene = new TransformSystem();
	sceneManager.AddScene(new Scene(renderSystemForDefaultScene, transformSystemForDefaultScene), "defaultScene.json");

	CameraComponent* cameraForTestingScene = new CameraComponent({ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) });
	RenderSystem* renderSystemForTestingScene = new RenderSystem(_renderer, cameraForTestingScene);
	TransformSystem* transformSystemForTestingScene = new TransformSystem();
	sceneManager.AddScene(new Scene(renderSystemForTestingScene, transformSystemForTestingScene), "testingScene.json");
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

void GameEngine::Update(Uint32 deltaTime) {

	if (mode == Mode::RUN || mode == Mode::RUN_DEBUG) 
		_game.Update(deltaTime);

	if (mode == Mode::EDIT) {
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame(_window);
		ImGui::NewFrame();

		GameGUI::ShowEditorMainMenuBar(this);
		GameGUI::ShowEditorGameControlBar(this);
		GameGUI::ShowEditorSceneHierachy(&sceneManager);
		GameGUI::ShowEditorEntityProperties();

		ImGui::ShowDemoWindow();
	}

	sceneManager.GetCurrentScene()->Update();
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