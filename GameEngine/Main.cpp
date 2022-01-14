#include <SDL.h>
#include "GameEngine.h"
#include "EngineRunner.h"
#include "WindowGUI.h"

int main(int argc, char* args[]) {
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	const Uint32 MIN_FPS = 6;

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initalize SDL: %s", SDL_GetError());
		return 1;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 3;
	}

	WindowGUI::Init(window, renderer);

	GameEngine* gameEngine = new GameEngine(window, renderer);
	EngineRunner::Loop(gameEngine, MIN_FPS);

	WindowGUI::Shutdown();

	delete gameEngine;
	return 0;
}