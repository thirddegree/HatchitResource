/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 ThirdDegree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

#include <ht_platform.h>
#include <ht_noncopy.h>
#include <ht_refcounted.h>
#include <ht_singleton.h>
#include <ht_file.h>
#include <map>
#include <type_traits>
#include <ht_path_singleton.h>
#include <ht_jsonhelper.h>
#include <fstream>
#include <utility>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        class HT_API FileResource : public Core::RefCounted<ResourceType>
        {
        public:
            virtual ~FileResource() { };

            template<typename... Args>
            static Core::Handle<const ResourceType> GetHandle(const std::string& ID, Args&&... args)
            {
                Core::Handle<ResourceType> handle = Core::RefCounted<ResourceType>::GetHandle(ID, std::forward<Args>(args)...);
                if (handle.IsValid() /*&& handle->VInitFromFile(ID)*/)
                    return handle.template StaticCastHandle<const ResourceType>();
                else
                    return Core::Handle<const ResourceType>();
            }

            static Core::Handle<const ResourceType> GetHandleFromFileName(const std::string& fileName);

        protected:
            FileResource(Core::Guid ID);
        };
    }
}

/*
    Here's how the classes are going to be structured for resources:
    Resource<T> is the base class for all resources that have to be loaded / generated
    T is going to be the actual implementation of the data.
    Then we create a TPtr alias that is equivalent to Resource<T>::Handle
*/

#include <ht_resource.inl>
