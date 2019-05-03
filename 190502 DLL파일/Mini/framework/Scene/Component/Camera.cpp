#include "Framework.h"
#include "Camera.h"

Camera::Camera(Context * context)
    : position(0, 0, 0)
    , right(1, 0, 0)
    , up(0, 1, 0)
    , forward(0, 0, 1)
    , nearPlane(0.0f)
    , farPlane(1.0f)
{
    timer = context->GetSubsystem<Timer>();
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
            position += up * 200 * timer->GetDeltaTimeSec();
        else if (input->KeyPress(KeyCode::KEY_S))
            position -= up * 200 * timer->GetDeltaTimeSec();

        if (input->KeyPress(KeyCode::KEY_A))
            position -= right * 200 * timer->GetDeltaTimeSec();
        if (input->KeyPress(KeyCode::KEY_D))
            position += right * 200 * timer->GetDeltaTimeSec();
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
        &(position + forward),
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
