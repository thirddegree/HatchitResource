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
#include <ht_noncopy.h>
#include <mutex>

namespace Hatchit
{
    namespace Resource
    {
        template<typename Type>
        class Resource;

        template <typename Type>
        class HT_API Handle
        {
        public:
            Handle();
            Handle(const Handle& rhs);
            Handle(Handle&& rhs);
            ~Handle();

            Handle& operator=(const Handle& rhs);
            Handle& operator=(Handle&& rhs);

            Type* operator->() const;

            bool operator>(const Handle<Type>& rhs) const;
            bool operator<(const Handle<Type>& rhs) const;
            bool operator==(const Handle<Type>& rhs) const;
            bool operator!=(const Handle<Type>& rhs) const;

            bool IsValid() const;

            void Release();

        private:
            Type*       m_data;
            uint32_t*   m_count;
            mutable std::mutex m_mutex;

            Handle(Type* data, uint32_t* count);

            friend class Resource<Type>;
        };

        template <typename Type>
        class HT_API Resource : public Core::INonCopy
        {
        public:
            Resource() = default;
            Resource(Resource&&) = default;
            virtual ~Resource() = default;

            Resource& operator=(Resource&&) = default;

        };
    }
}

#include <ht_handle.inl>

