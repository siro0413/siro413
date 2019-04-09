#pragma once
#include "isubsystem.h"
class Graphics final :public ISubsystem
{
public:
	Graphics(Context* context);
	~Graphics();

	const bool Initialize() override;

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const uint& width, const uint& height);


private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swaoChain; //더블 버퍼링에 관련된 함수 

	//gpu에들어가기위해 view가붙음
	ID3D11RenderTargetView* rtv;	//더블 버퍼링에 그릴 도화지를 까는 함수
	D3D11_VIEWPORT voewprot;		//뭔가 그려지는 공간
	D3DXCOLOR clearColor;			//FLOAT값이기에 0~1 만씀

};

