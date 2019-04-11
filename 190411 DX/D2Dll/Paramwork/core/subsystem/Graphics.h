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
	IDXGISwapChain* swaoChain; //���� ���۸��� ���õ� �Լ� 

	//gpu���������� view������
	ID3D11RenderTargetView* rtv;	//���� ���۸��� �׸� ��ȭ���� ��� �Լ�
	D3D11_VIEWPORT voewprot;		//���� �׷����� ����
	D3DXCOLOR clearColor;			//FLOAT���̱⿡ 0~1 ����

};

