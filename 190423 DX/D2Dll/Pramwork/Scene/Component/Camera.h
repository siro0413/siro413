#pragma once

class Camera final
{
public:
	Camera(class Context* context);
	~Camera();

	auto GetViewMatrix() const -> const D3DXMATRIX& { return view; }
	auto GetProjMatrix() const -> const D3DXMATRIX& { return proj; }

	auto GetPosition() const -> const D3DXVECTOR3& { return position; }
	void SetPosition(const D3DXVECTOR3& position);

	void Update();



private:
	void UpdateViewMatrix();
	void UpdateProjMatrix();

	Input* input;

	D3DXVECTOR3 position;
	D3DXVECTOR3 righit;
	D3DXVECTOR3 up;
	D3DXVECTOR3 down;

	D3DXMATRIX view;
	D3DXMATRIX proj;

	float nearPlane;
	float farPlane;
};

