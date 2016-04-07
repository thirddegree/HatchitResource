#pragma once

#include <ht_resource.h>
#include <cassert>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        FileResource<ResourceType>::FileResource(std::string fileName) : Core::RefCounted<ResourceType>(std::move(fileName)) {};

        template<typename ResourceType>
        Core::Handle<const ResourceType> FileResource<ResourceType>::GetHandleFromFileName(const std::string& fileName)
        {
            return GetHandle(fileName, fileName);
        }
    }
}