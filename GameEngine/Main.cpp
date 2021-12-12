#include <iostream>
#include <SDL.h>
#include "Game.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* args[]) {
	const Uint32 MIN_FPS = 6;
	Uint32 min_delta_time = 1000 / MIN_FPS;
	Uint32 last_step = SDL_GetTicks();

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(1200, 800, SDL_WINDOW_SHOWN, &window, &renderer);
	Game* game = new Game(window, renderer);

	while (game->running) {
		Uint32 current_step = SDL_GetTicks();

		if (last_step < current_step) {
			Uint32 delta_time = current_step - last_step;
			if (delta_time > min_delta_time) {
				delta_time = min_delta_time;
			}

			game->Input();
			game->Update(delta_time);
			game->Render();

			last_step = current_step;
		}
		else {
			SDL_Delay(1);
		}
	}

	delete game;
	return 0;
}