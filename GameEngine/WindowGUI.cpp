#include "WindowGUI.h"
#include "GUIStyle.h"

void WindowGUI::Init(SDL_Window* window, SDL_Renderer* renderer)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	GUIStyle::SetupGUIStyle(&ImGui::GetStyle());

	ImGui_ImplSDL2_InitForSDLRenderer(window);
	ImGui_ImplSDLRenderer_Init(renderer);
}

void WindowGUI::Shutdown()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
