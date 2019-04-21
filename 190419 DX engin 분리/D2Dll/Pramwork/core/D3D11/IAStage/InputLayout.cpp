#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout(Context * context)
	:inputLayout(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();
}

InputLayout::~InputLayout()
{
	Clear();
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * descs, const uint & count, ID3DBlob * blob)
{
	if (descs == nullptr || count == 0)
		assert(false);

	auto hr = graphics->GetDevice()->CreateInputLayout
	(
		descs,
		count,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout

	);
	assert(SUCCEEDED(hr));
}


void InputLayout::Create(ID3DBlob * blob)
{
	if (blob == nullptr)
		assert(false);

	//Create Shader reflector
	ID3D11ShaderReflection* reflector = nullptr;
	auto hr = D3DReflect
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		/*IID_ID3D11ShaderReflection,*/
		__uuidof(ID3D11ShaderReflection),
		reinterpret_cast<void**>(&reflector)
	);
	assert(SUCCEEDED(hr));
}

void InputLayout::Clear()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::BindPipeline()
{
	graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
}
