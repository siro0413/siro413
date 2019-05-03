#include "Framework.h"
#include "IResource.h"

IResource::IResource(Context * context)
    : context(context)
    , resourceName("")
    , resourcePath("")
    , resourceType(ResourceType::Unknown)
{
    //TODO : resourceManager ó��
}

template <typename T>
constexpr ResourceType IResource::DeduceResourceType()
{
    return ResourceType::Unknown;
}

//Explicit template instantiation - ����� ���ø� �ν��Ͻ�(Ư��ȭ)

#define REGISTER_RESOURCE_TYPE(T, enumT) template <> ResourceType IResource::DeduceResourceType<T>() { return enumT; }
REGISTER_RESOURCE_TYPE(Texture, ResourceType::Texture)

