#pragma once

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
    class Input* input;
	class SceneManager* sManager;
};