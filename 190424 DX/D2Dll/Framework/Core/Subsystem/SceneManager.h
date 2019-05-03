#pragma once
#include "ISubsystem.h"
class SceneManager final : public ISubsystem
{
public:
	SceneManager(class Context* context);
	~SceneManager();

	const bool Initialize() override;

	auto getCurrScene() const -> class Scene* { return currScene; }
	void setCurrScene(const std::string& name);

	void RegisterScene(const std::string& name, class Scene* scene);

	void Update();
	void Render();

private:
	class Scene* currScene;
	std::map<std::string, class Scene*> scenes;
};