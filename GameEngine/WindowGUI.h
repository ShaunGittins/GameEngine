#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#pragma once
static class WindowGUI
{
public:
	static void Init(SDL_Window* window, SDL_Renderer* renderer);

	static void Shutdown();
};

