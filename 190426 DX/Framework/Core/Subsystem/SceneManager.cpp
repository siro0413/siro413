#include "stdafx.h"
#include "SceneManager.h"
#include "../../Scene/Scene.h"

SceneManager::SceneManager(Context * context)
    : ISubsystem(context)
    , currentScene(nullptr)
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
    SetCurrentScene("First");

    return true;
}

void SceneManager::SetCurrentScene(const std::string & name)
{
    assert(scenes.count(name) > 0);
    currentScene = scenes[name];
}

void SceneManager::RegisterScene(const std::string & name, Scene * scene)
{
    assert(scenes.count(name) < 1);
    scene->SetName(name);
    scenes[name] = scene;
}

void SceneManager::Update()
{
    if(currentScene)
        currentScene->Update();
}

void SceneManager::Render()
{
    if (currentScene)
        currentScene->Render();
}
