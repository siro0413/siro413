#include "stdafx.h"
#include "engine.h"

Engine::Engine()
{
	context = new Context();
	graphics = context->RegisterSubsystem<Graphics>(); 

	context->Intialize(); //Graphics의 Intialize가 불러와짐

	//===========================// 추후 분리예정
	//면의 기본 정점은 삼각형
	/* 찍는 순서  0-1-2
			1	
	
		0	2
	*/

	//Create VerTex Data
	{
		vertices = new VertexColor[3]; //배열이기때문에 DELETE_ARRAY
		vertices[0].position = D3DXVECTOR3{ -0.5f,-0.5f,0.0f };
		vertices[0].color = D3DXCOLOR{ 1.0f,0.0f,0.0f,1.0f }; //불투명하지않으니까 a값은 1

		vertices[1].position = D3DXVECTOR3{ +0.5f,+0.5f,0.0f };
		vertices[1].color = D3DXCOLOR{ 1.0f,1.0f,0.0f,1.0f }; //불투명하지않으니까 a값은 1

		vertices[2].position = D3DXVECTOR3{ +0.5f,-0.5f,0.0f };
		vertices[2].color = D3DXCOLOR{ 0.0f,0.0f,1.0f,1.0f }; //불투명하지않으니까 a값은 1

	}

	//Create Vertex Buffer //COM엔 DESC가 필수
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		//buffer를 사용할방법 DEFAULT는 CPU에서 접근불가 GPU에선 읽고쓰기 가능
		desc.Usage = D3D11_USAGE_DEFAULT;
		//BindFlags 파이라인 어디에 묶을것인가 
		//VERTEX_BUFFER형태로 묶을것이다
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//Byte의 크기 얼만큼 사용할건지 VertexColor의 3배만큼 (위에서 사용한것이 3개)
		desc.ByteWidth = sizeof(VertexColor) * 3;

		D3D11_SUBRESOURCE_DATA subData; // 얘한테 위에 정보를주고 (Create VerTex Data) 버퍼를만듬
		ZeroMemory(&subData, sizeof(D3D10_SUBRESOURCE_DATA));
		subData.pSysMem = vertices; //주소를 넣으면되기에 vertices자체를 넣음

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
		HRESULT hr = D3DX11CompileFromFileA //A =아스키 W = while차형
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
		HRESULT hr = D3DX11CompileFromFileA //A =아스키 W = while차형
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
		//positoin, color 데이터 2개
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
			12, //position 에서 12바이트를 사용했기떄문에 12바이트
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
	//stride 보폭
	uint stride = sizeof(VertexColor);
	uint offset = 0;
	//auto graphics = context->GetSubsystem<Graphics>();
	graphics->BeginScene();
	{
		graphics->GetDeviceContex()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
		//여기까지하면 점을 그리는지 선을그리는지 모름
		graphics->GetDeviceContex()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphics->GetDeviceContex()->VSSetShader(vertexShader, nullptr, 0);
		graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		
		graphics->GetDeviceContex()->Draw(3, 0);

	}
	graphics->EndScene();
}
