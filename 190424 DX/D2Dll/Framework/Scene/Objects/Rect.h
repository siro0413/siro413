#pragma once
class Rect final
{
public:
	Rect(class Context* context);
	~Rect();

	void Update();
	void Render();
private:
	class Context* context;
	class Graphics* graphics;

	Geometry<VertexTexture> geometry;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	InputLayout* inputLayout;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ConstantBuffer* worldBuffer;

	D3DXMATRIX world;

	ID3D11RasterizerState* rsState;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;

	ID3D11BlendState* blendState;
};