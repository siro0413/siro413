#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Context * context)
	: context(context)
{
	graphics = context->GetSubsystem<Graphics>();

	geometry.AddVertex(VertexTexture({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f }));
	geometry.AddVertex(VertexTexture({ -0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f }));
	geometry.AddVertex(VertexTexture({ +0.5f, -0.5f, 0.0f }, { 2.0f, 1.0f }));
	geometry.AddVertex(VertexTexture({ +0.5f, +0.5f, 0.0f }, { 2.0f, 0.0f }));

	geometry.AddIndex(0); geometry.AddIndex(1); geometry.AddIndex(2);
	geometry.AddIndex(2); geometry.AddIndex(1); geometry.AddIndex(3);

	vertexBuffer = new VertexBuffer(context);
	vertexBuffer->Create(geometry.GetVertices());

	indexBuffer = new IndexBuffer(context);
	indexBuffer->Create(geometry.GetIndices());

	vertexShader = new VertexShader(context);
	vertexShader->Create("TextureCoord.hlsl");

	pixelShader = new PixelShader(context);
	pixelShader->Create("TextureCoord.hlsl");

	inputLayout = new InputLayout(context);
	inputLayout->Create(vertexShader->GetBlob());

	worldBuffer = new ConstantBuffer(context);
	worldBuffer->Create<WorldData>();

	//Create World, View, Projection
	{
		D3DXMatrixIdentity(&world);
	}

	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, 1000, 1000, 1);
	//D3DXMatrixRotationZ(&R, static_cast<float>(D3DXToRadian(45)));
	D3DXMatrixTranslation(&T, 100, 100, 0);

	world = S * T;

	//Create Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false;

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState
		(
			&desc,
			&rsState
		);
		assert(SUCCEEDED(hr));
	}

	//Create ShaderResourceView
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			graphics->GetDevice(),
			L"Tree.png",
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = D3DX11CreateShaderResourceViewFromFile
		(
			graphics->GetDevice(),
			L"forest1.png",
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

		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = graphics->GetDevice()->CreateBlendState
		(
			&desc,
			&blendState
		);
		assert(SUCCEEDED(hr));
	}
}

Rect::~Rect()
{
	SAFE_RELEASE(blendState);
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rsState);

	SAFE_DELETE(worldBuffer);
	SAFE_DELETE(pixelShader);
	SAFE_DELETE(vertexShader);
	SAFE_DELETE(inputLayout);
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
}

void Rect::Update()
{
	auto data = worldBuffer->Map<WorldData>();
	{
		D3DXMatrixTranspose(&data->World, &world);
	}
	worldBuffer->Unmap();
}

void Rect::Render()
{
	vertexBuffer->BindPipeline();
	indexBuffer->BindPipeline();
	inputLayout->BindPipeline();
	vertexShader->BindPipeline();
	pixelShader->BindPipeline();
	worldBuffer->BindPipeline(ShaderStage::VS, 1);
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	graphics->GetDeviceContext()->RSSetState(rsState);
	graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &srv);
	graphics->GetDeviceContext()->PSSetShaderResources(1, 1, &srv1);
	graphics->GetDeviceContext()->OMSetBlendState(blendState, nullptr, 0xffffffff);
	graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
}
