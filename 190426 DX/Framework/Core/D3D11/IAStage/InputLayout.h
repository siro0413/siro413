#pragma once

class InputLayout final
{
public:
    InputLayout(class Context* context);
    ~InputLayout();

    void Create
    (
        D3D11_INPUT_ELEMENT_DESC* descs,
        const uint& count,
        ID3DBlob* blob
    );

    void Create(ID3DBlob* blob);

    void Clear();
    void BindPipeline();

private:
    class Graphics* graphics;
    ID3D11InputLayout* inputLayout;
};