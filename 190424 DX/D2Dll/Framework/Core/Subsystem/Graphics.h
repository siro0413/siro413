#pragma once
#include "ISubsystem.h"

class Graphics final : public ISubsystem
{
public:
    Graphics(Context* context);
    ~Graphics();

    const bool Initialize() override;

    auto GetDevice() const -> ID3D11Device* { return device; }
    auto GetDeviceContext() const -> ID3D11DeviceContext* { return deviceContext; }
    auto GetSwapChain() const -> IDXGISwapChain* { return swapChain; }

    void BeginScene();
    void EndScene();

private:
    void CreateBackBuffer(const uint& width, const uint& height);

private:
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    IDXGISwapChain* swapChain;

    ID3D11RenderTargetView* rtv;
    D3D11_VIEWPORT viewport;
    D3DXCOLOR clearColor;
};