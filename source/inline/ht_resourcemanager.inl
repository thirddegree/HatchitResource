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

#include <ht_resourcemanager.h>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Resource
    {
        inline ResourceManager::ResourceManager()
        {
        }

        inline ResourceManager::~ResourceManager()
        {
            /**
            * Check the resources map to
            * see if there are still any resources
            * that are alive.
            */
            if (m_resources.size() > 0)
            {
                /**
                * Output Error for each
                * resource, as we should not have resources
                * still alive at this point.
                */
                for (auto resource : m_resources)
                {
                    HT_ERROR_PRINTF("Resource Alive: %d\n", resource.first);
                }
            }
        }

        template <typename T, typename... Args>
        inline T* ResourceManager::GetResource(uint64_t id, Args&&... arguments)
        {
            if (id == -1) //invalid ID
                return nullptr;

            ResourceManager& _instance = ResourceManager::GetInstance();

            /**
            * Search for resource in map. If we don't find it
            * then this is an attempt to load a new resource.
            */
            auto it = _instance.m_resources.find(id);
            if (it == _instance.m_resources.end())
            {
                /**
                * Attempt to create a new resource of type T
                * NOTE:
                *   Pay close attention to the constructor here.
                *   Every single resource class MUST have a constructor
                *   that provides a single argument of uint64_t to respresent
                *   the unique identifier for that resource.
                *
                *   This also means that the [id] value MUST be unique. Otherwise
                *   the creation will fail the existence test, and the previously
                *   loaded resource with that [id] will be returned.
                *
                *   It is assumed that the user will define an Initialize function
                *   that will have variable arguments used for initialization
                *   of the actual resource. This allows us to generically
                *   create these resources from just this one factory function.
                *
                *   IMPORTANT:
                *       There will also most likely need to be a thread-safe
                *       version of this factory function that will be used
                *       in creation of resource in a thread other than the main
                *       application thread. (e.g. for streaming content)
                */
                T* resource = new T(id);
                if (!resource->Initialize(std::forward<Args>(arguments)))
                {
                    delete resource;
                    return nullptr;
                }
                _instance.m_resources.insert(std::make_pair(id, resource));
            }

            return reinterpret_cast<T*>(_instance.m_resources[id]);
        }

        template <typename T>
        void ResourceManager::ReleaseResource(uint64_t id)
        {
            ResourceManager& _instance = ResourceManager::instance();

            auto it = _instance.m_resources.find(id);
            if (it != _instance.m_resources.end())
            {
                delete (reinterpret_cast<T*>(_instance.m_resources[id]));

                _instance.m_resources.erase(it);
            }
        }

    }
}