#include <iostream>
#include <SDL.h>
#include "GameEngine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "GUIStyle.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;



int main(int argc, char* args[]) {
	const Uint32 MIN_FPS = 6;
	Uint32 min_delta_time = 1000 / MIN_FPS;
	Uint32 last_step = SDL_GetTicks();

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}
	GameEngine* gameEngine = new GameEngine(window, renderer);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	GUIStyle::SetupGUIStyle(&ImGui::GetStyle());

	ImGui_ImplSDL2_InitForSDLRenderer(window);
	ImGui_ImplSDLRenderer_Init(renderer);

	while (gameEngine->running) {
		Uint32 current_step = SDL_GetTicks();

		if (last_step < current_step) {
			Uint32 delta_time = current_step - last_step;
			if (delta_time > min_delta_time) {
				delta_time = min_delta_time;
			}

			gameEngine->Input();
			gameEngine->Update(delta_time);
			gameEngine->Render();

			last_step = current_step;
		}
		else {
			SDL_Delay(1);
		}
	}

	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	delete gameEngine;
	return 0;
}