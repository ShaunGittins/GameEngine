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
	int GetSceneNumber(Scene* scene);

	void Update();
	void Render();

	std::vector<Scene*> _scenes;

private:
	int _currentScene = 0;
};