#pragma once

enum class ResourceType : uint
{
    Unknown,
    Texture,
    Mesh,
    Material,
    Animation,
    Audio,
};

class IResource
{
public:
    template <typename T>
    static constexpr ResourceType DeduceResourceType();

public:
    IResource(class Context* context);
    virtual ~IResource() = default;

    virtual void SaveToFile(const std::string& path) = 0;
    virtual void LoadFromFile(const std::string& path) = 0;

    auto GetResourceName() const -> const std::string& { return resourceName; }
    void SetResourceName(const std::string& name) { this->resourceName = name; }

    auto GetResourcePath() const -> const std::string& { return resourcePath; }
    void SetResourcePath(const std::string& path) { this->resourcePath = path; }

    auto GetResourceType() const -> const ResourceType& { return resourceType; }
    void SetResourceType(const ResourceType& type) { this->resourceType = type; }

protected:
    class Context* context;
    class ResourceManager* resourceManager;

    std::string resourceName;
    std::string resourcePath;
    ResourceType resourceType;
};

