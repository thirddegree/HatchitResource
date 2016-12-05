/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_fileresource.h>
#include <ht_hash.h>

namespace Hatchit
{
    namespace Resource
    {
        template <typename T>
        FileResource<T>::FileResource(uint64_t id)
            : Resource<T>(std::move(id))
        {

        }

        template <typename T>
        template <typename... Args>
        static Handle<const T> FileResource<T>::GetHandle(const std::string& path, Args&&... args)
        {
            /**
            * We need to retrieve a resource handle using
            * the file path. This means we must convert this path value,
            * to a unique identifier. (or in future we change this signature to take both
            * the identifier and path)
            */
            uint64_t id = Core::Hash::FNV1A(path);
            Handle<T> handle = Resource<T>::GetHandle(id, std::forward<Args>(args)...);
            if (handle.IsValid())
            {
                //If the returned handle is valid.
                //We will cast to the corresponding resource type and return.
                return handle.template StaticCast<const T>();
            }
            else
                return Handle<const T>();
        }
    }
}