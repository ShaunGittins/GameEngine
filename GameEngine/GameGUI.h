#pragma once
#include "GameEngine.h"
#include "Scene.h"

class GameGUI
{
public:
    static void ShowEditorMainMenuBar(GameEngine* gameEngine);

    static void ShowEditorMenuFile(GameEngine* gameEngine);

    static void ShowEditorGameControlBar(GameEngine* gameEngine);

    static void ShowEditorSceneHierachy(SceneManager* sceneManager);

    static void ShowEditorEntityProperties();

    static void ShowEditorEntityPropertiesID();

    static void ShowEditorEntityPropertiesRenderComponent();

    static void ShowEditorEntityPropertiesTransformComponent();
};

