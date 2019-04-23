#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Context * context)
	: position(0, 0, 0)
	, righit(1, 0, 0)
	, up(0, 1, 0)
	, down(0, 0, 1)
	, nearPlane(0.0f)
	, farPlane(1.0f)
{
	input = context->GetSubsystem<Input>();

	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&proj);
}

Camera::~Camera()
{
}

void Camera::SetPosition(const D3DXVECTOR3 & position)
{
	this->position = position;
}

void Camera::Update()
{
	if (input->KeyPress(KeyCode::KEY_SHIFT))
	{
		if (input->KeyPress(KeyCode::KEY_W))
			position += up * 10;

		else if (input->KeyPress(KeyCode::KEY_S))
			position -= up * 10;

		if (input->KeyPress(KeyCode::KEY_A))
			position -= righit * 10;

		else if (input->KeyPress(KeyCode::KEY_D))
			position += righit * 10;
	}

	UpdateViewMatrix();
	UpdateProjMatrix();
}

void Camera::UpdateViewMatrix()
{
	D3DXMatrixLookAtLH
	(
		&view,
		&position,
		&(position+down),
		&up
	);
}

void Camera::UpdateProjMatrix()
{
	D3DXMatrixOrthoLH
	(
		&proj,
		Settings::Get().GetWidth(),
		Settings::Get().GetHeight(),
		nearPlane,
		farPlane
	);
}
