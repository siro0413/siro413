#include "stdafx.h"
#include "Texture.h"

Texture::Texture(Context * context)
	: IResource(context)
	,srv(nullptr)
	,format(DXGI_FORMAT_R8G8B8A8_UNORM)
	,width(0)
	,height(0)
{
	graphics = context->GetSubsystem<Graphics>();
}

Texture::~Texture()
{
	Clear();
}

void Texture::SaveToFile(const std::string & path)
{
}

void Texture::LoadFromFile(const std::string & path)
{
}

void Texture::CreateShaderResource(const std::string & path)
{
	this->resourcePath = path;
	//이함수가 저어어어아래 구현을 압축해준것
	auto hr = D3DX11CreateShaderResourceViewFromFileA
	(
		graphics->GetDevice(),
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* srcTexture = nullptr;
	srv->GetResource(reinterpret_cast<ID3D11Resource**>(&srcTexture));
	//자기가 가지는함수를 뺴주는 함수 resource

	D3D11_TEXTURE2D_DESC desc;
	srcTexture->GetDesc(&desc);

	width = desc.Width;
	height = desc.Height;
	format = desc.Format;

	SAFE_RELEASE(srcTexture);

}

void Texture::CreateShaderResource(const uint & width, const uint & height, const DXGI_FORMAT & format)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = width;
	desc.Height = height;
	//mipmap 
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* textuer = nullptr;
	auto hr = graphics->GetDevice()->CreateTexture2D
	(
		&desc,
		nullptr,
		&textuer
	);
	assert(SUCCEEDED(hr));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	//내가만들 차원을 어떻게만들건지 D3D11_SRV_DIMENSION_TEXTURE2D 2d로만들것이다.
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = desc.Format;
	//MostDetailedMip 디테일
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = graphics->GetDevice()->CreateShaderResourceView
	(
		textuer,
		&srvDesc,
		&srv
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(textuer);

}

void Texture::Clear()
{
	SAFE_RELEASE(srv);
	format = DXGI_FORMAT_R8G8B8A8_UNORM;
	width = 0;
	height = 0;
}

void Texture::BindPipeline(const ShaderStage & stage, const uint & slot)
{
	switch (stage)
	{
	case ShaderStage::VS:graphics->GetDeviceContext()->VSSetShaderResources(slot, 1, &srv);break;
	case ShaderStage::PS:graphics->GetDeviceContext()->PSSetShaderResources(slot, 1, &srv);break;
	case ShaderStage::GS:graphics->GetDeviceContext()->GSSetShaderResources(slot, 1, &srv);break;
	case ShaderStage::CS:graphics->GetDeviceContext()->CSSetShaderResources(slot, 1, &srv);break;

	}
}

