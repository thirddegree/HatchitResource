#pragma once

#include <ht_resource.h>
#include <ht_resourcemanager.h>
#include <cassert>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        FileResource<ResourceType>::FileResource(std::string fileName) : Core::RefCounted<ResourceType>(std::move(fileName)) {};

        template<typename ResourceType>
        Core::Handle<const ResourceType> FileResource<ResourceType>::GetHandle(const std::string& fileName)
        {
            Core::Handle<ResourceType> handle = RefCounted::GetHandle(fileName);
            if (handle.IsValid() && handle->VInitFromFile(fileName))
                return handle.StaticCastHandle<const ResourceType>();
            else
                return Core::Handle<const ResourceType>();
        }
    }
}