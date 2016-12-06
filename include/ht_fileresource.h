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
#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        template <typename T>
        class HT_API FileResource : public Resource<T>
        {
        public:
            virtual ~FileResource() {};

            template <typename... Args>
            static Handle<const T> GetHandle(Args&&... args);

        protected:
            FileResource(uint64_t id);
        };
    }
}

#include <ht_fileresource.inl>