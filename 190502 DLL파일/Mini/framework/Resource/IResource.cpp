#include "Framework.h"
#include "IResource.h"

IResource::IResource(Context * context)
    : context(context)
    , resourceName("")
    , resourcePath("")
    , resourceType(ResourceType::Unknown)
{
    //TODO : resourceManager 처리
}

template <typename T>
constexpr ResourceType IResource::DeduceResourceType()
{
    return ResourceType::Unknown;
}

//Explicit template instantiation - 명시적 템플릿 인스턴스(특수화)

#define REGISTER_RESOURCE_TYPE(T, enumT) template <> ResourceType IResource::DeduceResourceType<T>() { return enumT; }
REGISTER_RESOURCE_TYPE(Texture, ResourceType::Texture)

