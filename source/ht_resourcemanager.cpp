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

#include <ht_resourcemanager.h>

namespace Hatchit
{
    namespace Resource
    {
        ResourceManager::ResourceManager()
        {

        }

        ResourceManager::~ResourceManager()
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
                for (auto& resource : m_resources)
                {
                    HT_ERROR_PRINTF("Resource Alive: %d\n", resource.first);
                }
            }
        }

        ResourceManager& ResourceManager::GetInstance()
        {
            return ResourceManager::instance();
        }
    }
}