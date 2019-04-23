#include "stdafx.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(Context * context)
	:buffer(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

ConstantBuffer::~ConstantBuffer()
{
	Clear();
}

void ConstantBuffer::Clear()
{
	SAFE_RELEASE(buffer);
}

void ConstantBuffer::BindPipeline(const ShaderStage & stage, const uint & slot)
{
	switch (stage)
	{
	case ShaderStage::VS: graphics->GetDeviceContex()->VSSetConstantBuffers(slot, 1, &buffer); break;
	case ShaderStage::PS: graphics->GetDeviceContex()->PSSetConstantBuffers(slot, 1, &buffer); break;
	case ShaderStage::GS: graphics->GetDeviceContex()->GSSetConstantBuffers(slot, 1, &buffer); break;
	case ShaderStage::CS: graphics->GetDeviceContex()->CSSetConstantBuffers(slot, 1, &buffer); break;
	}
}

void ConstantBuffer::Unmap()
{
	graphics->GetDeviceContex()->Unmap(buffer, 0);
}
