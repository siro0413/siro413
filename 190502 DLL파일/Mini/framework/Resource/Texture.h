#pragma once
#include "IResource.h"

class Texture final : public IResource
{
public:
    Texture(class Context* context);
    ~Texture();

    void SaveToFile(const std::string & path) override;
    void LoadFromFile(const std::string & path) override;

    auto GetShaderResource() const -> ID3D11ShaderResourceView* { return srv; }
    auto GetFormat() const -> const DXGI_FORMAT& { return format; }
    auto GetWidth() const -> const uint& { return width; }
    auto GetHeight() const -> const uint& { return height; }

    void CreateShaderResource(const std::string& path);
    void CreateShaderResource(const uint& width, const uint& height, const DXGI_FORMAT& format);
    void Clear();
    void BindPipeline(const ShaderStage& stage, const uint& slot);

private:
    class Graphics* graphics;
    ID3D11ShaderResourceView* srv;
    DXGI_FORMAT format;
    uint width;
    uint height;
};