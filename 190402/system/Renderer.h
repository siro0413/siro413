#pragma once

//Singleton Pattern

//class GameObject;//전방선언
class Renderer
{
public:
    static Renderer& Get()
    {
        static Renderer instance;
        return instance;
    }

    void Render(class GameObject* object);
    void Render(const struct Pos& pos, const char* str);

private:
    Renderer() = default;
    ~Renderer() = default;

private:
    void MoveCursor(const struct Pos& pos, const char* str);
};