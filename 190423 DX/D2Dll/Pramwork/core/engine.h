#pragma once

//시작점 모든걸 다가지고있을예정 (main급)
class Engine final
{
public:
	Engine();
	~Engine();

	auto GetContext() const -> class Context* { return context; }


	void Update();
	void Render();


private:
	class Context* context;
	class Graphics* graphics;
	class Input* input;

	//===========================//
	class Camera* camera;
	Geometry<VertexTexture> geometry;

	//↓IA에 들어가기위해 변환하는 함수
	//ID3D11Buffer* vertexBuffer;
	///IndexBuffer
	//ID3D11Buffer* IndexBuffer;
	///틀
	//ID3D11InputLayout* inputLayout;
	///Shader
	//ID3D11VertexShader* vertexShader;
	//ID3D11PixelShader* pixelShader;
	//↑ 바꾸기전 ↓바꾼후
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	InputLayout* inputLayout;
	VertexShader * vertexShader;
	PixelShader* pixelShader;
	//Blob shader가 제대로 컴파일이되었는지 확인해주는함수
	//ID3DBlob* vsBlob; ← VertexShader에서 사용했기에 지움
	//ID3DBlob* psBlob; ← PixelShader에서 사용했기에 지움
	ConstantBuffer* transformBuffer;

	//공간변화는 shader
	D3DXMATRIX world;

	////buffer로쓰면 헷갈리니 c= 상수를 붙임
	//ID3D11Buffer* cbuffer;

	ID3D11RasterizerState* rsState;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;

	//ID3D11Texture2D -> 포켓몬 이브이같은애 여러가지로 변형이가능
	
	ID3D11BlendState* blendState; //OM부분 혼합
};
