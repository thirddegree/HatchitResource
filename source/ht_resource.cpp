/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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

#include <ht_resource.h>

namespace Hatchit {

    namespace Resource {

        Resource::Resource()
        {
            m_refcount = 1;
        }

        Resource::~Resource()
        {

        }

        void Resource::IncrementRef()
        {
            m_refcount++;
        }

        void Resource::DecrementRef()
        {
            if(m_refcount > 0)
                m_refcount--;
        }

        uint32_t Resource::RefCount()
        {
            return m_refcount;
        }

    }

}
