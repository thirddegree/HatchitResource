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

#include <ht_platform.h>
#include <ht_singleton.h>
#include <ht_string.h>
#include <map>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API ResourceManager : public Core::Singleton<ResourceManager>
        {
        public:
            static void Initialize();

            static void DeInitialize();

            template<typename ResourceType>
            static ResourceType* GetRawPointer(const std::string& name);

            template<typename ResourceType>
            static void ReleaseRawPointer(const std::string& name);

        private:
            static ResourceManager& GetInstance();

            std::map<std::string, void*> m_resources;
        };

        template <typename ResourceType>
        ResourceType* ResourceManager::GetRawPointer(const std::string& name)
        {
            if (name.empty())
                return nullptr;

            ResourceManager& _instance = ResourceManager::GetInstance();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(name);
            if (it == _instance.m_resources.end())
            {
                //Resource not found. Must allocate
                ResourceType* resource = new ResourceType(name);
                if (!resource->VInitFromFile(name))
                {
                    delete resource;
                    return nullptr;
                }
                _instance.m_resources.insert(std::make_pair(name, resource));
            }
            
            return reinterpret_cast<ResourceType*>(_instance.m_resources[name]);
        }

        template<typename ResourceType>
        void ResourceManager::ReleaseRawPointer(const std::string& name)
        {
            ResourceManager& _instance = ResourceManager::GetInstance();

            std::map<std::string, void*>::iterator it = _instance.m_resources.find(name);
            if (it != _instance.m_resources.end())
            {
                delete (reinterpret_cast<ResourceType*>(_instance.m_resources[name]));

                _instance.m_resources.erase(it);
            }
        }
    }
}
