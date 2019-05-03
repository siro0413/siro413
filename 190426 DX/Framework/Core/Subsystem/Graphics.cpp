#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics(Context * context)
    : ISubsystem(context)
    , device(nullptr)
    , deviceContext(nullptr)
    , swapChain(nullptr)
    , rtv(nullptr)
    , clearColor(0xFF555566)
{
}

Graphics::~Graphics()
{
}

const bool Graphics::Initialize()
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.BufferDesc.Width                   = 0;
    desc.BufferDesc.Height                  = 0;
    desc.BufferDesc.RefreshRate.Numerator   = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
    desc.BufferCount                        = 1;
    desc.SampleDesc.Count                   = 1;
    desc.SampleDesc.Quality                 = 0;
    desc.OutputWindow                       = Settings::Get().GetWindowHandle();
    desc.Windowed                           = TRUE;
    desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    D3D_FEATURE_LEVEL featureLevels[] = 
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevels,
        1,
        D3D11_SDK_VERSION,
        &desc,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    );
    assert(SUCCEEDED(hr));

    CreateBackBuffer
    (
        static_cast<uint>(Settings::Get().GetWidth()),
        static_cast<uint>(Settings::Get().GetHeight())
    );

    return true;
}

void Graphics::BeginScene()
{
    deviceContext->RSSetViewports(1, &viewport);
    deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
    deviceContext->ClearRenderTargetView(rtv, clearColor);
}

void Graphics::EndScene()
{
    HRESULT hr = swapChain->Present(1, 0);
    assert(SUCCEEDED(hr));
}

void Graphics::CreateBackBuffer(const uint & width, const uint & height)
{
    HRESULT hr = swapChain->ResizeBuffers
    (
        0,
        width,
        height,
        DXGI_FORMAT_UNKNOWN, //infrastructure
        0
    );
    assert(SUCCEEDED(hr));

    ID3D11Texture2D* backBuffer = nullptr;
    hr = swapChain->GetBuffer
    (
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backBuffer)
    );
    assert(SUCCEEDED(hr));

    hr = device->CreateRenderTargetView
    (
        backBuffer,
        nullptr,
        &rtv
    );
    assert(SUCCEEDED(hr));

    viewport.TopLeftX   = 0.0f;
    viewport.TopLeftY   = 0.0f;
    viewport.Width      = static_cast<float>(width);
    viewport.Height     = static_cast<float>(height);
    viewport.MinDepth   = 0.0f;
    viewport.MaxDepth   = 1.0f;

    SAFE_RELEASE(backBuffer);
}
