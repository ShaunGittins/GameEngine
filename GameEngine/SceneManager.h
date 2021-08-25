#pragma once
#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void AddScene(Scene scene);
	Scene* GetCurrentScene();

private:
	std::vector<Scene> _scenes;
};