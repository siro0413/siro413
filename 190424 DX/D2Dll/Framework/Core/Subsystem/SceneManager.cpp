#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"

SceneManager::SceneManager(Context * context)
	: ISubsystem(context)
	, currScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	for (auto& scene : scenes)
		SAFE_DELETE(scene.second);
}

const bool SceneManager::Initialize()
{
	RegisterScene("First", new Scene(context));
	setCurrScene("First");

	return true;
}

void SceneManager::setCurrScene(const std::string & name)
{
	assert(scenes.count(name) > 0);
	currScene = scenes[name];
}

void SceneManager::RegisterScene(const std::string & name, Scene * scene)
{
	assert(scenes.count(name) < 1);
	scene->setName(name);
	scenes[name] = scene;
}

void SceneManager::Update()
{
	if(currScene)
		currScene->Update();
}

void SceneManager::Render()
{
	if(currScene)
		currScene->Render();
}
