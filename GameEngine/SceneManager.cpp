#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	_scenes.clear();
}

void SceneManager::AddScene(Scene scene)
{
	_scenes.push_back(scene);
}

Scene* SceneManager::GetCurrentScene()
{
	return &_scenes[0];
}
