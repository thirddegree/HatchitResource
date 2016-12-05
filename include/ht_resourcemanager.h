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
#include <map>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API ResourceManager : public Core::Singleton<ResourceManager>
        {
        public:
            ResourceManager();

            ~ResourceManager();

            template <typename T, typename... Args>
            static T* GetResource(uint64_t id, Args&&... arguments);

            template <typename T>
            static void ReleaseResource(uint64_t id);

        private:
            std::map<uint64_t, void*> m_resources;

            static ResourceManager& GetInstance();
        };
    }
}