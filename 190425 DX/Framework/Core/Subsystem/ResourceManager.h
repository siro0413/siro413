#pragma once
#include "ISubsystem.h"
#include "Framework/Resource/IResource.h"

class ResourceManager final :public ISubsystem
{
public:
	ResourceManager(class Context* context);
	~ResourceManager();

	const bool Initialize() override;

	template <typename T> auto Load(const std::string& path)->T*;
	template <typename T> auto GetResourceFromName(const std::string& name)->T*;
	template <typename T> auto GetResourceFromPath(const std::string& path)->T*;
	template <typename T> auto GetResourceDirectory() -> const std::string;
	
	void RegisterResource(IResource* resource);
	void RegisterResourceDirectory(const ResourceType& type, const std::string& directory);

private:
	typedef std::vector<IResource*> ResourceGroup;
	std::map<ResourceType, ResourceGroup> resourceGroups;
	std::map<ResourceType, std::string> resourceDirectories;

};

template<typename T>
inline auto ResourceManager::Load(const std::string & path) -> T *
{
	return NULL;
}

template<typename T>
inline auto ResourceManager::GetResourceFromName(const std::string & name) -> T *
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement Iresource");
	for (auto resouce : resourceGroups[IResource::DeduceResourceType<T>])
	{
		if (resouce->GetResourceName() == name)
			return static_cast<T*>(resouce);
	}
		return nullptr;
}

template<typename T>
inline auto ResourceManager::GetResourceFromPath(const std::string & path) -> T *
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement Iresource");
	for (auto resouce : resourceGroups[IResource::DeduceResourceType<T>])
	{
		if (resouce->GetResourcePath() == name)
			return static_cast<T*>(resouce);
	}
	return NULL;
}

template<typename T>
inline auto ResourceManager::GetResourceDirectory() -> const std::string
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement Iresource");
	return resourceDirectories[IResource::DeduceResourceType<T>()];
}
