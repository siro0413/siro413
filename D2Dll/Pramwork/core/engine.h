#pragma once

//시작점 모든걸 다가지고있을예정 (main급)
class Engine final
{
public:
	Engine();
	~Engine();

	auto GetContext() const -> class Context* { return context; }


	void Update();
	void Render();


private:
	class Context* context;
	class Graphics* graphics;
};
