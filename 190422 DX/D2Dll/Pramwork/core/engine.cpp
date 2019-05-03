#include "stdafx.h"
#include "engine.h"

Engine::Engine()
{
	context = new Context();
	graphics = context->RegisterSubsystem<Graphics>(); 

	context->Intialize(); //Graphics�� Intialize�� �ҷ�����

	//���� �⺻ ������ �ﰢ��
	/* ��� ����  0-1-2
		1	3	
	
		0	2
	*/


	
	geometry.AddVertex(VertexTexture({ -0.5f,-0.5f,0.0f }, { 0.0f,1.0f }));
	geometry.AddVertex(VertexTexture({ -0.5f,+0.5f,0.0f }, { 0.0f,0.0f }));
	geometry.AddVertex(VertexTexture({ +0.5f,-0.5f,0.0f }, { 2.0f,1.0f }));
	geometry.AddVertex(VertexTexture({ +0.5f,+0.5f,0.0f }, { 2.0f,0.0f }));

	//Create Index DatA
	geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
	geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);



	vertexBuffer = new VertexBuffer(context);
	vertexBuffer->Create(geometry.GetVertices()); 
	// �� template�ε� <>�Ⱦ��� ������ ��Ȯ�ϱ⶧����
	// ������ Create<VertexBuffer>
	indexBuffer = new IndexBuffer(context);
	indexBuffer->Create(geometry.GetIndices());


	//Create Vertex Shader
	{
		HRESULT hr = D3DX11CompileFromFileA //A =�ƽ�Ű W = while����
		(
			"Texture.hlsl",
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
			"TextureCode.hlsl",
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

	inputLayout = new InputLayout(context);
	//inputLayout->Create(VertexTexture::descs, VertexTexture::count, vsBlob);
	inputLayout->Create(vsBlob);

	//Create World, View, Projection
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&proj);

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

		//D3DXMatrixOrthoOffCenterLH
		//(
		//    &proj,
		//    0.0f,
		//    Settings::Get().GetWidth(),
		//    0.0f,
		//    Settings::Get().GetHeight(),
		//    0.0f,
		//    1.0f
		//);
	}
	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D10_BUFFER_DESC));
		//���÷� ������Ʈ cpu�� �������ְ� gpu�� ���������ִ��Լ� /�ӵ��� ����
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		//cpu�� ���ٰ������� ����¿���
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//��������� ������ �˸��̴� ���÷ξ�����Ʈ�Ǳ⿡ �ȳ־��

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			nullptr,
			&cbuffer
		);
		assert(SUCCEEDED(hr));
	}
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, 500, 500, 1);
	//D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
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

	world = S * T;

	std::cout << std::endl;
	std::cout << world._11 << " " << world._12 << " " << world._13 << " " << world._14 << std::endl;
	std::cout << world._21 << " " << world._22 << " " << world._23 << " " << world._24 << std::endl;
	std::cout << world._31 << " " << world._32 << " " << world._33 << " " << world._34 << std::endl;
	std::cout << world._41 << " " << world._42 << " " << world._43 << " " << world._44 << std::endl;

	//scali * �� * �� * �� * ��
	//ȸ�� * ���� * �̵� * ���� *�θ�

	//Crate Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		//D3D11_CULL_FRONT �ո�, BACK �޸�
		desc.CullMode = D3D11_CULL_BACK;
		//CounterClock �ݽð���� �׸��� ���������� �ո�޸��Ǵ�
		//ex-> �ð�����̸� �ո� �ݽð�����̸� �޸�
		desc.FrontCounterClockwise = false;
		//FrontCounterClockwise �޸����׸������ƴ���. false�� �ո� true�� �޸�

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState
		(
			&desc,
			&rsState
		);
		assert(SUCCEEDED(hr));
	}

	//uv �̹����ؽ��� ������ǥ
	//Create ShaderResourceView
	{
		//D3DX11�� ���߿� �Ⱦ��� �Լ�
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			graphics->GetDevice(),
			L"Tree.png",//������ �����̸�
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		assert(SUCCEEDED(hr));


		//D3DX11�� ���߿� �Ⱦ��� �Լ�
		 hr = D3DX11CreateShaderResourceViewFromFile
		(
			graphics->GetDevice(),
			L"Black1.png",//������ �����̸�
			nullptr,
			nullptr,
			&srv1,
			nullptr
		);
		assert(SUCCEEDED(hr));

	}

	//Create Blend State
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;
		//src�� �޸� �ؽ���
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		//dest�� �������� �ؽ��� invers
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		//op ������ add 
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		//�޸� 1 �ո�0 �ΰ����ؼ� 1 ���� �޸��̳���
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		//���� ��ɾ��� ALL�� ������ Ư������ �Է��ϸ� �׻����̿���
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = graphics->GetDevice()->CreateBlendState
		(
			&desc,
			&blendState
		);
		assert(SUCCEEDED(hr));

	}

}

Engine::~Engine()
{
	SAFE_RELEASE(blendState);
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rsState);
	SAFE_RELEASE(cbuffer);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);

	SAFE_DELETE(inputLayout);
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
	SAFE_DELETE(context);
}

void Engine::Update()
{
	////���� ũ�⺯��
	//world._11 = 100;
	//world._22 = 100;
	////������ �̵�
	//world._41 = 100; //������
	//world._42 = 100; //����
	//D3DXMATRIX S, R, T;
	//D3DXMatrixScaling(&S,100,100,1);
	//D3DXMatrixTranslation(&T, 100, 100, 0);

	//world = S * T;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		world._42 += 5;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		world._42 -= 5;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		world._41 -= 5;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		world._41 += 5;


	D3DXMatrixTranspose(&data.World, &world);
	D3DXMatrixTranspose(&data.View, &view);
	D3DXMatrixTranspose(&data.Proj, &proj);

	D3D11_MAPPED_SUBRESOURCE subResource;
	//map Unmap ������� ���ڽ��̿� �ƹ��� �����������ϰ� ���¿�Ȱ(look,unlook)
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
	
	//auto graphics = context->GetSubsystem<Graphics>();
	graphics->BeginScene();
	{
		//graphics->GetDeviceContex()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		// �� ������ �� ������
		vertexBuffer->BindPipeline();

		
		//format = �տ� DXGI_FORMAT_ �����̰� �������� ������� 
		//graphics->GetDeviceContex()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		// �� ������ �� ������
		indexBuffer->BindPipeline();
		//graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
		// �� ������ �� ������
		inputLayout->BindPipeline();
		//��������ϸ� ���� �׸����� �����׸����� ��
		graphics->GetDeviceContex()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		
		graphics->GetDeviceContex()->VSSetShader(vertexShader, nullptr, 0);
		graphics->GetDeviceContex()->VSSetConstantBuffers(0, 1, &cbuffer);

		graphics->GetDeviceContex()->RSSetState(rsState);

		graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		graphics->GetDeviceContex()->PSSetShaderResources(0, 1, &srv);
		graphics->GetDeviceContex()->PSSetShaderResources(1, 1, &srv1);


		graphics->GetDeviceContex()->OMSetBlendState(blendState, nullptr,0xffffffff);
		
		graphics->GetDeviceContex()->DrawIndexed(6,0,0);


	}
	graphics->EndScene();
}