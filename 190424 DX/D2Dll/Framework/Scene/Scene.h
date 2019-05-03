#pragma once

class Scene final
{
public:
	Scene(class Context* context);
	~Scene();

	auto getName() const -> const std::string& { return name; }
	void setName(const std::string& name) { this->name = name; }

	void Update();
	void Render();

	private:
		class Context* context;
		class Camera* camera;
		std::string name;
		
		class ConstantBuffer* cameraBuffer;
		class Rect* rect1;
};