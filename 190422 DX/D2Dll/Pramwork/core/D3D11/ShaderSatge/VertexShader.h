#pragma once

class VertexShader
{
public:
	VertexShader(class Context* context);
	~VertexShader();

	void Create
	(
		const std::string& path,
		const std::string& entryPoint = "VS",
		const std::string& shaderModel = "vs_5_0",
		D3D_SHADER_MACRO* defines = nullptr
	);
	void Clear();
	void BindPipeline();

private:
	class Graphics* graphics;
	ID3D11VertexShader* shader;
	ID3DBlob* blob;
	std::string path;
	std::string entryPoint;
	std::string shaderModel;
};


