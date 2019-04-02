#include "stdafx.h"
#include "SceneManager.h"
#include "./Scene/IScene.h"

void SceneManager::SetCurrentScene(const std::string & sceneName)
{
	//assert(scenes.count(sceneName) > 0);
	CurrentScene = scenes[sceneName];

}

void SceneManager::AddScene(const std::string & sceneName, IScene * scene)
{
	//assert(scenes.count(sceneName)< 1);

	//1
	//scenes[sceneName] = scene;

	//2
	std::pair<std::string, IScene*>pair;
	scenes.insert(std::make_pair(sceneName, scene));
}

void SceneManager::Update()
{
	//dangling pointer
	if(CurrentScene)
		CurrentScene->Update();
}

void SceneManager::Render()
{
	if (CurrentScene)
		CurrentScene->Render();
}

SceneManager::SceneManager()
	:CurrentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	//scenes.clear();
	//정석
	//std::map<std::string, IScene*>::iterator iter = scenes.begin();
	//for (; iter != scenes.end(); iter++)
	//{
	//	delete iter->second;
	//}

	//간단하게
	for (auto& scene : scenes)
		delete scene.second;
}
