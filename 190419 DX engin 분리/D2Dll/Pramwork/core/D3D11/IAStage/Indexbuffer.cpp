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
	case D3D11_USAGE_IMMUTABLE: //GPU���� �б⸸ ����.CPU���� ���� ����!
	case D3D11_USAGE_DEFAULT:	//GPU�� ���ؼ� �а� ���� ������ ����.
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:	//GPU���� �б⸸, CPU������ ���⸸
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:	//GPU���� CPU�� ���� ����. (�����ٰ��� �а���)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;

	}

	desc.Usage = usage;
	//usage������ �ٲ�¾�(���̳���)
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
