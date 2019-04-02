#pragma once


class SceneManager final
{
public:

	static SceneManager& Get()
	{
		static SceneManager instance;
		return instance;
	}

	auto GetCurrentScene() const -> const class IScene* { return CurrentScene; }
	void SetCurrentScene(const std::string& sceneName);

	auto GetScenes() const -> const std::map<std::string, class IScene*>& { return scenes; }
	void AddScene(const std::string&sceneName, class IScene* scene);

	void Update();
	void Render();


private:
	SceneManager();
	~SceneManager();




private:
	class IScene* CurrentScene;
	std::map<std::string, class IScene*> scenes;
};

