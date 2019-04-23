#include "stdafx.h"
#include "engine.h"
#include "Pramwork/Scene/Component/Camera.h"
Engine::Engine()
{
	context = new Context();
	graphics = context->RegisterSubsystem<Graphics>(); 

	input = context->RegisterSubsystem<Input>();

	context->Intialize(); //Graphics�� Intialize�� �ҷ�����

	camera = new Camera(context);
	
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
	
	vertexShader = new VertexShader(context);
	vertexShader->Create("TextureCode.hlsl");

	pixelShader = new PixelShader(context);
	pixelShader->Create("TextureCode.hlsl");

	inputLayout = new InputLayout(context);
	inputLayout->Create(vertexShader->getBlob());
	
	transformBuffer = new ConstantBuffer(context);
	transformBuffer->Create<TransformData>();


	//Create World, View, Projection
	{
		D3DXMatrixIdentity(&world);
	}
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, 500, 500, 1);
	//D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
	D3DXMatrixTranslation(&T, 100, 100, 0);

	world = S * T;
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

	SAFE_DELETE(transformBuffer);
	SAFE_DELETE(pixelShader);
	SAFE_DELETE(vertexShader);
	SAFE_DELETE(inputLayout);
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
	SAFE_DELETE(camera);

	SAFE_DELETE(context);
}

void Engine::Update()
{

	input->Update();
	camera->Update();

	auto data = transformBuffer->Map<TransformData>();
	{
		D3DXMatrixTranspose(&data->World, &world);

		D3DXMatrixTranspose(&data->View, &camera->GetViewMatrix());
		D3DXMatrixTranspose(&data->Proj, &camera->GetProjMatrix());
	}
	transformBuffer->Unmap();

}

void Engine::Render()
{
	
	//auto graphics = context->GetSubsystem<Graphics>();
	graphics->BeginScene();
	{
		//graphics->GetDeviceContex()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		//graphics->GetDeviceContex()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		//graphics->GetDeviceContex()->IASetInputLayout(inputLayout);
		//graphics->GetDeviceContex()->VSSetShader(vertexShader, nullptr, 0);
		//graphics->GetDeviceContex()->VSSetConstantBuffers(0, 1, &cbuffer);
		//graphics->GetDeviceContex()->PSSetShader(pixelShader, nullptr, 0);
		// �� ������ �� ������
		vertexBuffer->BindPipeline();
		indexBuffer->BindPipeline();
		inputLayout->BindPipeline();
		vertexShader->BindPipeLine();
		pixelShader->BindPipeLine();
		transformBuffer->BindPipeline(ShaderStage::VS, 0);
				
		//format = �տ� DXGI_FORMAT_ �����̰� �������� ������� 
		//��������ϸ� ���� �׸����� �����׸����� ��
		graphics->GetDeviceContex()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				
		graphics->GetDeviceContex()->RSSetState(rsState);
			   
		graphics->GetDeviceContex()->PSSetShaderResources(0, 1, &srv);
		graphics->GetDeviceContex()->PSSetShaderResources(1, 1, &srv1);
		
		graphics->GetDeviceContex()->OMSetBlendState(blendState, nullptr,0xffffffff);
		
		graphics->GetDeviceContex()->DrawIndexed(6,0,0);


	}
	graphics->EndScene();
}
