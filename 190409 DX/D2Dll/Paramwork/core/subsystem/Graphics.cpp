#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics(Context * context)
	: ISubsystem(context)
	,device(nullptr)
	,deviceContext(nullptr)
	,swaoChain(nullptr)
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
	//새로고침 Numerator 분자 
	desc.BufferDesc.RefreshRate.Numerator = 60;
	//빈도 (화면갱신률) Denominator 분모 1초에 60번
	desc.BufferDesc.RefreshRate.Denominator = 1;
	//RGBA 각각 1바이트씩 (8bit)  UNORM 정규화된 양수 8비트가 정수화된다
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// UNSPECIFIED 구체화되지않음
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//비율
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//위에 버퍼카운트 숫자
	desc.BufferCount = 1;
	//SSAA
	//Super Sample
	//그림의 크기를 크게해서 부족한부분 채우고 다시줄임
	//소모량이 크다

	//MSAA
	//Multi Sample
	//4가지 점을찍고 판단 외각선만 샘플링을잡는다

	//샘플링을 한번
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//출력할 윈도우창 handle이들어감
	desc.OutputWindow = nullptr; //TODO : 내가 설정한 곳으로 이동이가능 (작업목록)
	//창모드 전체모드 
	desc.Windowed = TRUE;
	//창이 스왑될때 뒤에것을 지워라
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//버퍼를 랜더 타겟에 출력해라
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1, //뭔가 터지면 일단여기의심
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT hresult = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, //컴퓨터의 성능에따라 최적화할수있게만들어줌
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, 
		featureLevels,
		1,
		D3D11_SDK_VERSION, 
		&desc,
		&swaoChain,
		&device,
		nullptr,
		&deviceContext
	);

	assert(SUCCEEDED(hresult));
	return true;
}

void Graphics::BeginScene()
{
}

void Graphics::EndScene()
{
}

void Graphics::CreateBackBuffer(const uint & width, const uint & height)
{
	HRESULT hresult = swaoChain->ResizeBuffers 
	(
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN, //infrastructure 구조
		0
	);
	assert(SUCCEEDED(hresult));
	//cpu date = ID3D11Texture2D
	//설정한 3가지색으로 바꿀수있음
	ID3D11Texture2D* backBuffer = nullptr;
	hresult = swaoChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&backBuffer)
	);
	//UUID GUID
	//UUID 범용적인 고유 식별자
	//GUID 전역적인 고유 식별자
	assert(SUBLANGID(hresult));

}
