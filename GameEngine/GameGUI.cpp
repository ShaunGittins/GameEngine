#include "GameGUI.h"

#include <imgui_impl_sdlrenderer.h>
#include <imgui_impl_sdl.h>
#include <imgui_internal.h>

#include "Entity.h"
#include "NameComponent.h"
#include "ScriptComponent.h"

using std::to_string;

Entity* selectedEntity = nullptr;

void GameGUI::ShowEditorMainMenuBar(GameEngine* gameEngine)
{
    {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ShowEditorMenuFile(gameEngine);
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
}

void GameGUI::ShowEditorMenuFile(GameEngine* gameEngine)
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
        gameEngine->running = false;
    }
}

void GameGUI::ShowEditorGameControlBar(GameEngine* gameEngine)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    float height = ImGui::GetFrameHeight();

    if (ImGui::BeginViewportSideBar("##GameControlBar", NULL, ImGuiDir_Up, height, window_flags)) {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::ArrowButton("##run", ImGuiDir_Right)) { gameEngine->mode = Mode::RUN; }
            ImGui::EndMenuBar();
        }
    }
    ImGui::End();
}

void GameGUI::ShowEditorEntityList(Scene* currentScene)
{
    if (ImGui::Begin("Entities")) {
        if (ImGui::ListBoxHeader("Entities"))
        {
            for (Entity* entity : currentScene->entities)
            {
                string entityName = to_string(entity->_id);
                if (entity->GetComponent<NameComponent>()) {
                    entityName += " \"" + entity->GetComponent<NameComponent>()->_name + "\"";
                }
                bool isSelected = selectedEntity == entity;
                if (ImGui::Selectable(entityName.c_str(), isSelected))
                {
                    selectedEntity = entity;
                }
                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::ListBoxFooter();
        }
        ImGui::End();
    }
}

void GameGUI::ShowEditorEntityProperties()
{
    if (ImGui::Begin("Entity properties")) {
        if (selectedEntity != nullptr) {
            ShowEditorEntityPropertiesID();

            ImGui::Separator();

            ImGui::Text("Components:");
            ShowEditorEntityPropertiesRenderComponent();
            ShowEditorEntityPropertiesTransformComponent();
        }
        else {
            ImGui::Text("No entity selected");
        }

        ImGui::End();
    }
}

void GameGUI::ShowEditorEntityPropertiesID()
{
    string guiSelectedIdentifier = "id: " + to_string(selectedEntity->_id);

    if (selectedEntity->GetComponent<NameComponent>()) {
        guiSelectedIdentifier += " | name: \"" + selectedEntity->GetComponent<NameComponent>()->_name + "\"";
    }

    ImGui::Text(guiSelectedIdentifier.c_str());
}

void GameGUI::ShowEditorEntityPropertiesRenderComponent()
{
    if (RenderComponent* rc = selectedEntity->GetComponent<RenderComponent>()) {
        if (ImGui::CollapsingHeader("Render Component")) {
            ImGui::Checkbox("Visible", &rc->isVisible);
            ImGui::SliderInt("Layer", &rc->layer, 0, 10);

            if (rc->rects.size() > 0) {
                ImGui::Text("Primitives: ");
            }

            if (rc->sprites.size() > 0) {
                ImGui::Text("Sprite: ");
                Sprite* mySprite = *rc->sprites.begin();
                ImGui::Text(("File name: " + mySprite->filename).c_str());

                static float* position[2] = { &mySprite->rect.x, &mySprite->rect.y };
                ImGui::DragFloat2("Position relative", *(position));

                static float* scale[2] = { &mySprite->rect.w, &mySprite->rect.h };
                ImGui::DragFloat2("Size", *(scale));

                static float* pivot[2] = { &mySprite->rotationPoint.x, &mySprite->rotationPoint.y };
                ImGui::DragFloat2("Pivot point", *(pivot));

                ImGui::SliderFloat("Angle", &mySprite->angle, -360, 360, "%.0f deg", ImGuiSliderFlags_None);
                ImGui::Text(to_string(mySprite->angle).c_str());
            }
        }
    }
}

void GameGUI::ShowEditorEntityPropertiesTransformComponent()
{
    if (TransformComponent* tc = selectedEntity->GetComponent<TransformComponent>()) {
        if (ImGui::CollapsingHeader("Transform Component")) {
            ImGui::Text("Transform Component:");
            static float* position[2] = { &tc->_position._x, &tc->_position._y };
            ImGui::DragFloat2("position", *(position));

            ImGui::DragFloat("rotation", &tc->_rotation, 1.0f, 0.0f, 360.0f);

            static float* scale[2] = { &tc->_scale._x, &tc->_scale._y };
            ImGui::DragFloat2("scale", *(scale));
        }
    }
}

void GameGUI::ShowEditorEntityPropertiesScriptComponent()
{
    if (ScriptComponent* sc = selectedEntity->GetComponent<ScriptComponent>()) {
        if (ImGui::CollapsingHeader("Script Component")) {
            string fullName = "Script: " + sc->name;
            ImGui::Text(fullName.c_str());
        }
    }
}
