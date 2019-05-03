#include "Framework.h"
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
    //DXGI�� ����ϱ����� ���� �������̽����� ����������
    IDXGIFactory* factory = nullptr;
    auto hr = CreateDXGIFactory
    (
        __uuidof(IDXGIFactory),
        reinterpret_cast<void**>(&factory)
    );
    assert(SUCCEEDED(hr));

    //DXGI �߿� �׷���ī�� ���� ���
    IDXGIAdapter* adapter = nullptr;
    hr = factory->EnumAdapters(0, &adapter);
    assert(SUCCEEDED(hr));

    //�׷���ī���� ������ִ� ���÷��� ����
    IDXGIOutput* adapter_output = nullptr;
    hr = adapter->EnumOutputs(0, &adapter_output);
    assert(SUCCEEDED(hr));

    //���÷��� ��� ���� ���
    uint mode_count = 0;
    hr = adapter_output->GetDisplayModeList
    (
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_ENUM_MODES_INTERLACED,
        &mode_count,
        nullptr
    );
    assert(SUCCEEDED(hr));

    //���÷��� ��� ����Ʈ ���
    auto display_mode_list = new DXGI_MODE_DESC[mode_count];
    hr = adapter_output->GetDisplayModeList
    (
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_ENUM_MODES_INTERLACED,
        &mode_count,
        display_mode_list
    );
    assert(SUCCEEDED(hr));

    for (uint i = 0; i < mode_count; i++)
    {
        bool bCheck = true;
        bCheck &= display_mode_list[i].Width == static_cast<uint>(Settings::Get().GetWidth());
        bCheck &= display_mode_list[i].Height == static_cast<uint>(Settings::Get().GetHeight());

        if (bCheck)
        {
            numerator = display_mode_list[i].RefreshRate.Numerator;
            denomerator = display_mode_list[i].RefreshRate.Denominator;
        }
    }

    DXGI_ADAPTER_DESC adapter_desc;

    hr = adapter->GetDesc(&adapter_desc);
    assert(SUCCEEDED(hr));

    gpu_memory_size = adapter_desc.DedicatedVideoMemory / 1024 / 1024;
    gpu_description = adapter_desc.Description;

    SAFE_DELETE_ARRAY(display_mode_list);
    SAFE_RELEASE(adapter_output);
    SAFE_RELEASE(adapter);
    SAFE_RELEASE(factory);

    std::cout << numerator << std::endl;
    std::cout << denomerator << std::endl;
    std::cout << gpu_memory_size << std::endl;
    //std::cout << gpu_description << std::endl;

    CreateSwapChain();
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
    HRESULT hr = swapChain->Present(Settings::Get().IsVsync() ? 1 : 0, 0);
    assert(SUCCEEDED(hr));
}

void Graphics::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    desc.BufferDesc.Width = 0;
    desc.BufferDesc.Height = 0;
    desc.BufferDesc.RefreshRate.Numerator = Settings::Get().IsVsync() ? numerator : 0;
    desc.BufferDesc.RefreshRate.Denominator = Settings::Get().IsVsync() ? denomerator : 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    desc.BufferCount = 1;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.OutputWindow = Settings::Get().GetWindowHandle();
    desc.Windowed = TRUE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

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
