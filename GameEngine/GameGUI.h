#pragma once
#include "Game.h"
#include "Scene.h"


class GameGUI
{
public:

    static void ShowEditorMainMenuBar(Game* game);

    static void ShowEditorMenuFile(Game* game);

    static void ShowEditorGameControlBar(Game* game);

    static void ShowEditorEntityList(Scene* currentScene);

    static void ShowEditorEntityProperties();

    static void ShowEditorEntityPropertiesID();

    static void ShowEditorEntityPropertiesRenderComponent();

    static void ShowEditorEntityPropertiesTransformComponent();
};

