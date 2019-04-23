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
	class Input* input;

	//===========================//
	class Camera* camera;
	Geometry<VertexTexture> geometry;

	//��IA�� �������� ��ȯ�ϴ� �Լ�
	//ID3D11Buffer* vertexBuffer;
	///IndexBuffer
	//ID3D11Buffer* IndexBuffer;
	///Ʋ
	//ID3D11InputLayout* inputLayout;
	///Shader
	//ID3D11VertexShader* vertexShader;
	//ID3D11PixelShader* pixelShader;
	//�� �ٲٱ��� ��ٲ���
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	InputLayout* inputLayout;
	VertexShader * vertexShader;
	PixelShader* pixelShader;
	//Blob shader�� ����� �������̵Ǿ����� Ȯ�����ִ��Լ�
	//ID3DBlob* vsBlob; �� VertexShader���� ����߱⿡ ����
	//ID3DBlob* psBlob; �� PixelShader���� ����߱⿡ ����
	ConstantBuffer* transformBuffer;

	//������ȭ�� shader
	D3DXMATRIX world;

	////buffer�ξ��� �򰥸��� c= ����� ����
	//ID3D11Buffer* cbuffer;

	ID3D11RasterizerState* rsState;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;

	//ID3D11Texture2D -> ���ϸ� �̺��̰����� ���������� �����̰���
	
	ID3D11BlendState* blendState; //OM�κ� ȥ��
};
