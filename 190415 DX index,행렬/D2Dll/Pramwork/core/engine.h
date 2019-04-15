#pragma once
struct  VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};
//������ ���� �ٰ������������� (main��)
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

	//===========================//
	VertexColor* vertices;
	//��IA�� �������� ��ȯ�ϴ� �Լ�
	ID3D11Buffer* vertexBuffer;

	//IndexBuffer
	uint* indices;
	ID3D11Buffer* IndexBuffer;

	//Shader
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vsBlob;
	
	//Blob shader�� ����� �������̵Ǿ����� Ȯ�����ִ��Լ�
	ID3D11PixelShader* pixelShader;
	ID3DBlob* psBlob;
	
	//Ʋ
	ID3D11InputLayout* inputLayout;

	//������ȭ�� shader
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX proj;

	struct TransformData
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Proj;
	}data;
	//buffer�ξ��� �򰥸��� c= ����� ����
	ID3D11Buffer* cbuffer;

};
