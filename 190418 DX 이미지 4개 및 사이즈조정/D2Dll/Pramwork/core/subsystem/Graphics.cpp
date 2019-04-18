#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics(Context * context)
	: ISubsystem(context)
	,device(nullptr)
	,deviceContext(nullptr)
	,swapChain(nullptr)
	,rtv(nullptr)
	,clearColor(0xFF555566)
{
}

Graphics::~Graphics()
{
}

const bool Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	//���ΰ�ħ Numerator ���� 
	desc.BufferDesc.RefreshRate.Numerator = 60;
	//�� (ȭ�鰻�ŷ�) Denominator �и� 1�ʿ� 60��
	desc.BufferDesc.RefreshRate.Denominator = 1;
	//RGBA ���� 1����Ʈ�� (8bit)  UNORM ����ȭ�� ��� 8��Ʈ�� ����ȭ�ȴ�
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// UNSPECIFIED ��üȭ��������
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//����
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//���� ����ī��Ʈ ����
	desc.BufferCount = 1;
	//SSAA
	//Super Sample
	//�׸��� ũ�⸦ ũ���ؼ� �����Ѻκ� ä��� �ٽ�����
	//�Ҹ��� ũ��

	//MSAA
	//Multi Sample
	//4���� ������� �Ǵ� �ܰ����� ���ø�����´�

	//���ø��� �ѹ�
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//����� ������â handle�̵�
	desc.OutputWindow = Settings::Get().GetwindowHandle(); //TODO : ���� ������ ������ �̵��̰��� (�۾����)
	//â��� ��ü��� 
	desc.Windowed = TRUE;
	//â�� ���ҵɶ� �ڿ����� ������
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//���۸� ���� Ÿ�ٿ� ����ض�
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1, //���� ������ �ϴܿ����ǽ�
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT hresult = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, //��ǻ���� ���ɿ����� ����ȭ�Ҽ��ְԸ������
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

	assert(SUCCEEDED(hresult));

	CreateBackBuffer
	(
		static_cast<uint>(Settings::Get().GetWidth()),
		static_cast<uint>(Settings::Get().GetHeight())

	);
	return true;
}

void Graphics::BeginScene()
{
	deviceContext->RSSetViewports(1, &viewport); //RS�κп� �ش�
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);//OM�κп� �ش�
	deviceContext->ClearRenderTargetView(rtv, clearColor); //ȭ���� �����ϴ� �������°�(�̵�)
}

void Graphics::EndScene() //ȭ���� �����ִ¾�
{
	HRESULT hresult = swapChain->Present(1, 0);
	assert(SUCCEEDED(hresult));
}

void Graphics::CreateBackBuffer(const uint & width, const uint & height)
{
	HRESULT hresult = swapChain->ResizeBuffers  //swapChain�̵���ִ� �Ǵ�� ũ��
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN, //infrastructure ����
		0
	);
	assert(SUCCEEDED(hresult));
	//cpu date = ID3D11Texture2D
	//������ 3���������� �ٲܼ�����
	ID3D11Texture2D* backBuffer = nullptr;
	hresult = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&backBuffer)
	);
	//UUID GUID
	//UUID �������� ���� �ĺ���  16byte
	//GUID �������� ���� �ĺ���  
	assert(SUCCEEDED(hresult));

	hresult = device->CreateRenderTargetView
	(
		backBuffer,
		nullptr,
		&rtv
	);
	assert(SUCCEEDED(hresult));

	viewport.TopLeftX	= 0.0f;
	viewport.TopLeftY	= 0.0f;
	viewport.Width		= static_cast<float> (width);
	viewport.Height		= static_cast<float>(height);
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;


	SAFE_RELEASE(backBuffer);

}
