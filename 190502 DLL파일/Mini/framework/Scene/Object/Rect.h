#pragma once

class Rect final
{
public:
    Rect(class Context* context);
    ~Rect();

    void Update();
    void Render();

private:
    class Context* context;
    class Graphics* graphics;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    InputLayout* inputLayout;
    VertexShader* vertexShader;
    PixelShader* pixelShader;
    ConstantBuffer* worldBuffer;
    Texture* tex1;
    Texture* tex2;


    D3DXMATRIX world;

    ID3D11RasterizerState* rsState;
    ID3D11BlendState* blendState;
};