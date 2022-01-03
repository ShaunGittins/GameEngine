#pragma once

#include <imgui_impl_sdlrenderer.h>
#include <imgui_impl_sdl.h>
#include "Game.h"
#include <imgui_internal.h>

class GameGUI
{
public:
	static void ShowEditorMainMenuBar(Game* game) {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ShowEditorMenuFile(game);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
	}

    static void ShowEditorMenuFile(Game* game)
    {
        if (ImGui::MenuItem("New")) {}
        if (ImGui::MenuItem("Open", "Ctrl+O")) {}
        if (ImGui::BeginMenu("Open Recent")) {
            ImGui::MenuItem("test.game");
            ImGui::MenuItem("test2.game");
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Save", "Ctrl+S")) {}
        if (ImGui::MenuItem("Save As..")) {}

        ImGui::Separator();
        if (ImGui::MenuItem("Quit", "Alt+F4")) {
            game->running = false;
        }
    }

    static void ShowEditorGameControlBar(Game* game) {

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
        float height = ImGui::GetFrameHeight();

        if (ImGui::BeginViewportSideBar("##GameControlBar", NULL, ImGuiDir_Up, height, window_flags)) {
            if (ImGui::BeginMenuBar()) {
                if (ImGui::ArrowButton("##run", ImGuiDir_Right)) { game->mode = Mode::RUN; }
                ImGui::EndMenuBar();
            }
        }
        ImGui::End();
    }
};

