#pragma once
class VertexShader final
{
public:
	VertexShader(Context * context);
	~VertexShader();
	
	auto getBlob() const -> ID3DBlob* { return blob; }

	void Create
	(
		const std::string& path,
		const std::string& entryPoint = "VS",
		const std::string& shaderModel = "vs_5_0",
		D3D_SHADER_MACRO* defines = nullptr
	);
	void Clear();
	void BindPipeLine();

private:
	class Graphics* graphics;
	ID3D11VertexShader* shader;
	ID3DBlob* blob;
	std::string path;
	std::string entryPoint;
	std::string shaderModel;
};