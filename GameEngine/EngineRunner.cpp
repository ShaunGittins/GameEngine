#include "EngineRunner.h"

void EngineRunner::Loop(GameEngine* gameEngine, Uint32 min_fps)
{
	Uint32 min_delta_time = 1000 / min_fps;
	Uint32 last_step = SDL_GetTicks();
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
}
