#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (Scene* scene : _scenes) {
		delete scene;
	}
	_scenes.clear();
}

void SceneManager::AddScene(Scene* scene, string sceneFilename)
{
	scene->AddEntitiesFromJSON(sceneFilename);
	scene->name = sceneFilename;
	_scenes.push_back(scene);
}

Scene* SceneManager::GetCurrentScene()
{
	return _scenes[_currentScene];
}

Scene* SceneManager::GetScene(int sceneNumber)
{
	return _scenes[sceneNumber];
}

void SceneManager::SetScene(int scene)
{
	_currentScene = scene;
}

int SceneManager::GetCurrentSceneNumber()
{
	return _currentScene;
}

int SceneManager::GetSceneNumber(Scene* scene)
{
	auto it = std::find(_scenes.begin(), _scenes.end(), scene);

	if (it != _scenes.end())
		return (it - _scenes.begin());
	else 
		return -1;
}

void SceneManager::Update()
{
	GetCurrentScene()->Update();
}

void SceneManager::Render()
{
	GetCurrentScene()->Render();
}

