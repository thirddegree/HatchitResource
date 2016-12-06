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

#include <ht_resource.h>
#include <ht_resourcemanager.h>

namespace Hatchit
{
    namespace Resource
    {
        template <typename T>
        inline Resource<T>::Resource(uint64_t id)
            : m_count(),
              m_id(std::move(id))
        {

        }

        template <typename T>
        template <typename... Args>
        inline Handle<T> Resource<T>::GetHandle(uint64_t id, Args&&... args)
        {
            /**
            * Attempt to retrieve handle to resource type with
            * given [id] value. If an instance for this resource does not
            * exist, one will be created and a handle referencing this resource will
            * be returned.
            */
            T* resource = ResourceManager::GetResource<T, Args...>(std::move(id), std::forward<Args>(args)...);
            if (resource)
            {
                return Handle<T>(resource, &(resource->m_count), &(resource->m_id));
            }
            /**
            * If an invalid resource is returned, we will pass along an empty handle.
            */
            else
            {
                return Handle<T>();
            }
        }
    }
}