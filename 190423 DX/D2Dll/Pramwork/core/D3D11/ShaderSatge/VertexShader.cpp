#include "stdafx.h"
#include "VertexShader.h"
#include "Pramwork/core/D3D11/D3D11_Helper.h"

Context * context;
VertexShader::VertexShader(Context * context)
	: shader(nullptr)
	, blob(nullptr)
	, path("")
	, entryPoint("")
	, shaderModel("")
{
	graphics = context->GetSubsystem<Graphics>();
}

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(const std::string & path, const std::string & entryPoint, const std::string & shaderModel, D3D_SHADER_MACRO * defines)
{
	this->path = path;
	this->entryPoint = entryPoint;
	this->shaderModel = shaderModel;

	auto result = D3D11_Helper::CompileShader
	(
		path,
		entryPoint,
		shaderModel,
		defines,
		&blob
	);

	auto hr = graphics->GetDevice()->CreateVertexShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	assert(SUCCEEDED(hr));
}

void VertexShader::Clear()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void VertexShader::BindPipeLine()
{
	graphics->GetDeviceContex()->VSSetShader(shader, nullptr, 0);
}
