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
		1	3	
	
		0	2
	*/

	//Create VerTex Data
	{
		vertices = new VertexColor[4]; //배열이기때문에 DELETE_ARRAY
		vertices[0].position = D3DXVECTOR3{ -0.5f,-0.5f,0.0f };
		vertices[0].color = D3DXCOLOR{ 1.0f,0.0f,0.0f,1.0f }; //불투명하지않으니까 a값은 1

		vertices[1].position = D3DXVECTOR3{ -0.5f,+0.5f,0.0f };
		vertices[1].color = D3DXCOLOR{ 1.0f,1.0f,0.0f,1.0f }; 

		vertices[2].position = D3DXVECTOR3{ +0.5f,-0.5f,0.0f };
		vertices[2].color = D3DXCOLOR{ 0.0f,0.0f,1.0f,1.0f }; 

		vertices[3].position = D3DXVECTOR3{ +0.5f,+0.5f,0.0f };
		vertices[3].color = D3DXCOLOR{ 0.0f,1.0f,1.0f,1.0f };

	}

	//Create Vertex Buffer //COM엔 DESC가 필수
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		//buffer를 사용할방법 DEFAULT는 CPU에서 접근불가 GPU에선 읽고쓰기 가능
		desc.Usage = D3D11_USAGE_DEFAULT;
		//BindFlags 파이프라인 어디에 묶을것인가 
		//VERTEX_BUFFER형태로 묶을것이다
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//Byte의 크기 얼만큼 사용할건지 VertexColor의 3배만큼 (위에서 사용한것이 3개)
		desc.ByteWidth = sizeof(VertexColor) * 4;

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

	//Create Index DatA
	{
		indices = new uint[6]{ 0,1,2,2,1,3 };
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(uint) * 6;

		D3D11_SUBRESOURCE_DATA subdata;
		ZeroMemory(&subdata, sizeof(D3D11_SUBRESOURCE_DATA));
		subdata.pSysMem = indices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subdata,
			&IndexBuffer
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
	
	//Create World,view,projection
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&proj);
		//LH Z축좌표가 내반대로갈수록 + (시계방향)
		D3DXMatrixLookAtLH
		(
			&view,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 1),
			&D3DXVECTOR3(0, 1, 0)
		);

		D3DXMatrixOrthoLH
		(
			&proj,
			Settings::Get().GetWidth(),
			Settings::Get().GetHeight(),
			0.0f,
			1.0f
		);
	}

	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		//수시로 업데이트 cpu는 쓸수만있고 gpu는 읽을수만있는함수 /속도가 빠름
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		//cpu가 접근가능한지 물어보는여부
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//여기까지가 껍데기 알맹이는 수시로업데이트되기에 안넣어도됨

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			nullptr,
			&cbuffer
		);
		assert(SUCCEEDED(hr));
	}

}

Engine::~Engine()
{
	SAFE_RELEASE(cbuffer);
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE_ARRAY(indices);
	SAFE_DELETE_ARRAY(vertices);
	SAFE_DELETE(context);
}

void Engine::Update()
{
	world._11 = 100;
	world._22 = 100;

	data.World = world;
	data.View = view;
	data.Proj = proj;

	D3D11_MAPPED_SUBRESOURCE subResource;
	graphics->GetDeviceContex()->Map
	(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subResource
	);

	memcpy(subResource.pData, &data, sizeof(TransformData));

	graphics->GetDeviceContex()->Unmap(cbuffer, 0);
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
		//format = 앞에 DXGI_FORMAT_ 을붙이고 정수값을 넣으면됨 
		graphics->GetDeviceContex()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
		//여기까지하면 점을 그리는지 선을그리는지 모름
		graphics->GetDeviceContex()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		
		graphics->GetDeviceContex()->VSSetShader(vertexShader, nullptr, 0);
		graphics->GetDeviceContex()->VSSetConstantBuffers(0, 1, &cbuffer);


		graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		
		graphics->GetDeviceContex()->DrawIndexed(6,0,0);

	}
	graphics->EndScene();
}
