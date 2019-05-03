#pragma once

class Editor final
{
public:
	Editor();
	~Editor();

	void Resize(const uint& width, const uint& height);
	void Update();
	void Render();
private:
	class Context* context;
	class Engine* engine;
	class Graphics* graphics;

};
