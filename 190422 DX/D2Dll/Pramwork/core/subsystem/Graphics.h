#pragma once
#include "isubsystem.h"
class Graphics final :public ISubsystem
{
public:
	Graphics(Context* context);
	~Graphics();

	const bool Initialize() override;

	auto GetDevice() const -> ID3D11Device* { return device; }
	auto GetDeviceContex() const -> ID3D11DeviceContext* { return deviceContext; }
	auto GetSwapChin() const ->IDXGISwapChain* { return swapChain; }

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const uint& width, const uint& height);


private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain; //���� ���۸��� ���õ� �Լ� 

	//gpu���������� view������
	ID3D11RenderTargetView* rtv;	//���� ���۸��� �׸� ��ȭ���� ��� �Լ�
	D3D11_VIEWPORT viewport;		//���� �׷����� ����
	D3DXCOLOR clearColor;			//FLOAT���̱⿡ 0~1 ����

};

