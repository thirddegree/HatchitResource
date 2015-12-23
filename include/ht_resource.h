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

#pragma once

#include <ht_platform.h>
#include <ht_types.h>
#include <ht_noncopy.h>

namespace Hatchit {

    namespace Resource {

        class HT_API Resource : public Core::INonCopy
        {
        public:
            Resource();

            virtual ~Resource();

            virtual void IncrementRef();
            virtual void DecrementRef();

            uint32_t RefCount();

        private:
            uint32_t  m_refcount;
        };

    }

}
