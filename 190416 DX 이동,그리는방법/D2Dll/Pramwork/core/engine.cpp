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

		D3DXMatrixOrthoLH //중앙은 무조건 0,0  그래서 랜더링하면 항상 가운대
		(
			&proj,
			Settings::Get().GetWidth(),
			Settings::Get().GetHeight(),
			0.0f,
			1.0f
		);

		//D3DXMatrixOrthoOffCenterLH //마우스 좌표랑 같다
		//(
		//	&proj,
		//	0.0f,
		//	Settings::Get().GetWidth(),
		//	0.0f,
		//	Settings::Get().GetHeight(),
		//	0.0f,
		//	1.0f
		//);
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
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, 100, 100, 1);
	D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
	D3DXMatrixTranslation(&T, 100, 100, 0);
	
	std::cout << "S" << std::endl;
	std::cout << S._11 << " " << S._12 << " " << S._13 << " " << S._14 << std::endl;
	std::cout << S._21 << " " << S._22 << " " << S._23 << " " << S._24 << std::endl;
	std::cout << S._31 << " " << S._32 << " " << S._33 << " " << S._34 << std::endl;
	std::cout << S._41 << " " << S._42 << " " << S._43 << " " << S._44 << std::endl;

	std::cout << std::endl;
	std::cout << "R" << std::endl;

	std::cout << R._11 << " " << R._12 << " " << R._13 << " " << R._14 << std::endl;
	std::cout << R._21 << " " << R._22 << " " << R._23 << " " << R._24 << std::endl;
	std::cout << R._31 << " " << R._32 << " " << R._33 << " " << R._34 << std::endl;
	std::cout << R._41 << " " << R._42 << " " << R._43 << " " << R._44 << std::endl;

	std::cout << std::endl;
	std::cout << "T" << std::endl;

	std::cout << T._11 << " " << T._12 << " " << T._13 << " " << T._14 << std::endl;
	std::cout << T._21 << " " << T._22 << " " << T._23 << " " << T._24 << std::endl;
	std::cout << T._31 << " " << T._32 << " " << T._33 << " " << T._34 << std::endl;
	std::cout << T._41 << " " << T._42 << " " << T._43 << " " << T._44 << std::endl;

	world = S *R* T;

	std::cout << std::endl;
	std::cout << world._11 << " " << world._12 << " " << world._13 << " " << world._14 << std::endl;
	std::cout << world._21 << " " << world._22 << " " << world._23 << " " << world._24 << std::endl;
	std::cout << world._31 << " " << world._32 << " " << world._33 << " " << world._34 << std::endl;
	std::cout << world._41 << " " << world._42 << " " << world._43 << " " << world._44 << std::endl;

	//scali * 자 * 이 * 공 * 부
	//회전 * 자전 * 이동 * 공전 *부모

	//Crate Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		//D3D11_CULL_FRONT 앞면, BACK 뒷면
		desc.CullMode = D3D11_CULL_BACK;
		//CounterClock 반시계방향 그리는 순서에따라 앞면뒷면판단
		//ex-> 시계방향이면 앞면 반시계방향이면 뒷면
		desc.FrontCounterClockwise = false;
		//FrontCounterClockwise 뒷면을그릴건지아닌지. false는 앞면 true는 뒷면

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState
		(
			&desc,
			&rsState
		);
		assert(SUCCEEDED(hr));
	}
}

Engine::~Engine()
{
	SAFE_RELEASE(rsState);
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
	////비율 크기변경
	//world._11 = 100;
	//world._22 = 100;
	////공간의 이동
	//world._41 = 100; //오른쪽
	//world._42 = 100; //위로
	//D3DXMATRIX S, R, T;
	//D3DXMatrixScaling(&S,100,100,1);
	//D3DXMatrixTranslation(&T, 100, 100, 0);

	//world = S * T;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		world._42 += 5;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		world._42 -= 5;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		world._41 += 5;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		world._41 -= 5;


	D3DXMatrixTranspose(&data.World, &world);
	D3DXMatrixTranspose(&data.View, &view);
	D3DXMatrixTranspose(&data.Proj, &proj);

	D3D11_MAPPED_SUBRESOURCE subResource;
	//map Unmap 묶어놔서 나자신이외 아무도 접근하지못하게 막는역활(look,unlook)
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

		graphics->GetDeviceContex()->RSSetState(rsState);

		graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		
		graphics->GetDeviceContex()->DrawIndexed(6,0,0);


	}
	graphics->EndScene();
}
