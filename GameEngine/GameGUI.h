#pragma once
#include "GameEngine.h"
#include "Scene.h"


class GameGUI
{
public:

    static void ShowEditorMainMenuBar(GameEngine* game);

    static void ShowEditorMenuFile(GameEngine* game);

    static void ShowEditorGameControlBar(GameEngine* game);

    static void ShowEditorEntityList(Scene* currentScene);

    static void ShowEditorEntityProperties();

    static void ShowEditorEntityPropertiesID();

    static void ShowEditorEntityPropertiesRenderComponent();

    static void ShowEditorEntityPropertiesTransformComponent();
};

