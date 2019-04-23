#pragma once
class PixelShader final
{
public:
	PixelShader(class Context* context);
	~PixelShader();

	void Create
	(
		const std::string& path,
		const std::string& entryPoint = "PS",
		const std::string& shaderModel = "ps_5_0",
		D3D_SHADER_MACRO* defines = nullptr
	);
	void Clear();
	void BindPipeLine();

private:
	class Graphics* graphics;
	ID3D11PixelShader* shader;
	std::string path;
	std::string entryPoint;
	std::string shaderModel;
};