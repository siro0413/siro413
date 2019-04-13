#pragma once
struct  VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};
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
	//class Graphics* graphics2;

	//===========================//
	VertexColor* vertices;
	//VertexColor* vertices2;

	//↓IA에 들어가기위해 변환하는 함수
	ID3D11Buffer* vertexBuffer;

	//Shader
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vsBlob;
	
	//Blob shader가 제대로 컴파일이되었는지 확인해주는함수
	ID3D11PixelShader* pixelShader;
	ID3DBlob* psBlob;
	
	//틀
	ID3D11InputLayout* inputLayout;

};
