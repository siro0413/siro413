#pragma once
#include "ISubsystem.h"

class SceneManager final : public ISubsystem
{
public:
    SceneManager(class Context* context);
    ~SceneManager();

    const bool Initialize() override;

    auto GetCurrentScene() const -> class Scene* { return currentScene; }
    void SetCurrentScene(const std::string& name);

    void RegisterScene(const std::string& name, class Scene* scene);

    void Update();
    void Render();

private:
    class Scene* currentScene;
    std::map<std::string, class Scene*> scenes;
};