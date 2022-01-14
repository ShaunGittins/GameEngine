#include <iostream>
#include <SDL.h>
#include "GameEngine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "GUIStyle.h"
#include "EngineRunner.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	GUIStyle::SetupGUIStyle(&ImGui::GetStyle());

	ImGui_ImplSDL2_InitForSDLRenderer(window);
	ImGui_ImplSDLRenderer_Init(renderer);

	GameEngine* gameEngine = new GameEngine(window, renderer);
	const Uint32 MIN_FPS = 6;
	EngineRunner::Loop(gameEngine, MIN_FPS);

	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	delete gameEngine;
	return 0;
}