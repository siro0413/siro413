#pragma once

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
	Geometry<VertexTexture> geometry;


	//��IA�� �������� ��ȯ�ϴ� �Լ�
	ID3D11Buffer* vertexBuffer;

	//IndexBuffer

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

	ID3D11RasterizerState* rsState;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;

	//ID3D11Texture2D -> ���ϸ� �̺��̰����� ���������� �����̰���
	
	ID3D11BlendState* blendState; //OM�κ� ȥ��
};
