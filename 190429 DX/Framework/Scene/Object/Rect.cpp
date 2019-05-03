#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Context * context)
    : context(context)
{
    graphics = context->GetSubsystem<Graphics>();

    Geometry<VertexTexture> geometry;
    Geometry_Generator::CreateQuad(geometry);

    vertexBuffer = new VertexBuffer(context);
    vertexBuffer->Create(geometry.GetVertices());

    indexBuffer = new IndexBuffer(context);
    indexBuffer->Create(geometry.GetIndices());

    vertexShader = new VertexShader(context);
    vertexShader->Create("../_Assets/Shader/TextureCoord.hlsl");

    pixelShader = new PixelShader(context);
    pixelShader->Create("../_Assets/Shader/TextureCoord.hlsl");

    inputLayout = new InputLayout(context);
    inputLayout->Create(vertexShader->GetBlob());

    worldBuffer = new ConstantBuffer(context);
    worldBuffer->Create<WorldData>();

	////////////////////////////////////////////
	auto resourceManager = context->GetSubsystem<ResourceManager>();

	tex1 = resourceManager->Load<Texture>("Tree.png");
	tex2 = resourceManager->Load<Texture>("forest1.png");


	////////////////////////////////////////////

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
    SAFE_RELEASE(rsState);

	SAFE_DELETE(tex1);
	SAFE_DELETE(tex2);
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
	tex1->BindPipeline(ShaderStage::PS, 0);
	tex2->BindPipeline(ShaderStage::PS, 1);


    graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    graphics->GetDeviceContext()->RSSetState(rsState);


    graphics->GetDeviceContext()->OMSetBlendState(blendState, nullptr, 0xffffffff);

    graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
}
