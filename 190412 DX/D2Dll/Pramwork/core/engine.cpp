#include "stdafx.h"
#include "engine.h"

Engine::Engine()
{
	context = new Context();
	graphics = context->RegisterSubsystem<Graphics>(); 

	context->Intialize(); //Graphics�� Intialize�� �ҷ�����

	//===========================// ���� �и�����
	//���� �⺻ ������ �ﰢ��
	/* ��� ����  0-1-2
			1	
	
		0	2
	*/

	//Create VerTex Data
	{
		vertices = new VertexColor[3]; //�迭�̱⶧���� DELETE_ARRAY
		vertices[0].position = D3DXVECTOR3{ -0.5f,-0.5f,0.0f };
		vertices[0].color = D3DXCOLOR{ 1.0f,0.0f,0.0f,1.0f }; //���������������ϱ� a���� 1

		vertices[1].position = D3DXVECTOR3{ +0.5f,+0.5f,0.0f };
		vertices[1].color = D3DXCOLOR{ 1.0f,1.0f,0.0f,1.0f }; //���������������ϱ� a���� 1

		vertices[2].position = D3DXVECTOR3{ +0.5f,-0.5f,0.0f };
		vertices[2].color = D3DXCOLOR{ 0.0f,0.0f,1.0f,1.0f }; //���������������ϱ� a���� 1

	}

	//Create Vertex Buffer //COM�� DESC�� �ʼ�
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		//buffer�� ����ҹ�� DEFAULT�� CPU���� ���ٺҰ� GPU���� �а��� ����
		desc.Usage = D3D11_USAGE_DEFAULT;
		//BindFlags ���̶��� ��� �������ΰ� 
		//VERTEX_BUFFER���·� �������̴�
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//Byte�� ũ�� ��ŭ ����Ұ��� VertexColor�� 3�踸ŭ (������ ����Ѱ��� 3��)
		desc.ByteWidth = sizeof(VertexColor) * 3;

		D3D11_SUBRESOURCE_DATA subData; // ������ ���� �������ְ� (Create VerTex Data) ���۸�����
		ZeroMemory(&subData, sizeof(D3D10_SUBRESOURCE_DATA));
		subData.pSysMem = vertices; //�ּҸ� ������Ǳ⿡ vertices��ü�� ����

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subData,
			&vertexBuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Vertex Shader
	{
		HRESULT hr = D3DX11CompileFromFileA //A =�ƽ�Ű W = while����
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",//shader model
			0,
			0,
			nullptr,
			&vsBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));
		hr = graphics->GetDevice()->CreateVertexShader
		(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&vertexShader
		);
		assert(SUCCEEDED(hr));
	}
	//Create Piexl Shader
	{
		HRESULT hr = D3DX11CompileFromFileA //A =�ƽ�Ű W = while����
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",//shader model
			0,
			0,
			nullptr,
			&psBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));
		hr = graphics->GetDevice()->CreatePixelShader
		(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&pixelShader
		);
		assert(SUCCEEDED(hr));
	}

	//Create ImputLayout
	{
		//positoin, color ������ 2��
		D3D11_INPUT_ELEMENT_DESC layoutDescs[]=
		{
			{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
			{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12, //position ���� 12����Ʈ�� ����߱⋚���� 12����Ʈ
			D3D11_INPUT_PER_VERTEX_DATA,
			0 
			}
		};
		HRESULT hr = graphics->GetDevice()->CreateInputLayout
		(
			layoutDescs,
			2,
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout
		);
		assert(SUCCEEDED(hr));
	}

}




Engine::~Engine()
{
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE(context);
}

void Engine::Update()
{

}

void Engine::Render()
{
	//stride ����
	uint stride = sizeof(VertexColor);
	uint offset = 0;
	//auto graphics = context->GetSubsystem<Graphics>();
	graphics->BeginScene();
	{
		graphics->GetDeviceContex()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
		//��������ϸ� ���� �׸����� �����׸����� ��
		graphics->GetDeviceContex()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphics->GetDeviceContex()->VSSetShader(vertexShader, nullptr, 0);
		graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		
		graphics->GetDeviceContex()->Draw(3, 0);

	}
	graphics->EndScene();
}
