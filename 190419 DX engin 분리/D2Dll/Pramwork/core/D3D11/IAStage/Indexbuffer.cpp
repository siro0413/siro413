#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Context * context)
	:buffer(nullptr)
	,offset(0)
	,indexCount(0)
{
	graphics = context->GetSubsystem<Graphics>();
}

IndexBuffer::~IndexBuffer()
{
	Clear();
}

void IndexBuffer::Create(const std::vector<uint>& indices, const D3D11_USAGE & usage)
{
	indexCount = indices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	switch (usage)
	{
	case D3D11_USAGE_IMMUTABLE: //GPU에서 읽기만 가능.CPU에서 접근 급지!
	case D3D11_USAGE_DEFAULT:	//GPU에 의해서 읽고 쓰기 접근이 가능.
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:	//GPU에서 읽기만, CPU에서는 쓰기만
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:	//GPU에서 CPU로 값을 전달. (양방향다가능 읽고쓰기)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;

	}

	desc.Usage = usage;
	//usage에따라 바뀌는애(다이나믹)
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(uint) * indices.size();

	D3D11_SUBRESOURCE_DATA subDate;
	ZeroMemory(&subDate, sizeof(D3D11_SUBRESOURCE_DATA));
	subDate.pSysMem = indices.data();

	auto hr = graphics->GetDevice()->CreateBuffer
	(
		&desc,
		&subDate,
		&buffer
	);
	assert(SUCCEEDED(hr));
}

void IndexBuffer::Clear()
{
	SAFE_RELEASE(buffer);
	offset = 0;
	indexCount = 0;
}

void IndexBuffer::BindPipeline()
{
	graphics->GetDeviceContex()->IASetIndexBuffer
	(
		buffer,
		DXGI_FORMAT_R32_UINT,
		offset
	);

}
