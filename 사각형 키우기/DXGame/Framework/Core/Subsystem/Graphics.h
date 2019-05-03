#pragma once
#pragma once

class Graphics final
{
public:
	Graphics();
	~Graphics();

	void Initialize();

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	void BeginScene();
	void EndScene();

private:
	void CreateBackBuffer(const UINT& width, const UINT& height);

private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;

	ID3D11RenderTargetView* rtv;
	D3D11_VIEWPORT viewport;
	D3DXCOLOR clearColor;

};