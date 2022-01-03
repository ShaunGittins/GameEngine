#pragma once
#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void AddScene(Scene* scene, string sceneFilename);
	Scene* GetCurrentScene();
	Scene* GetScene(int sceneNumber);
	void SetScene(int sceneNumber);
	int GetCurrentSceneNumber();

	void Update();
	void Render();

private:
	int _currentScene = 0;
	std::vector<Scene*> _scenes;
};