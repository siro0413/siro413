#pragma once

class Scene final
{
public:
    Scene(class Context* context);
    ~Scene();

    auto GetName() const -> const std::string& { return name; }
    void SetName(const std::string& name) { this->name = name; }

    void Update();
    void Render();

private:
    class Context* context;
    std::string name;

    class Camera* camera;
    class ConstantBuffer* cameraBuffer;

    class Rect* rect1;
};