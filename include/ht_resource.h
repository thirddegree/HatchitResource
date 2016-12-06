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
        template<typename T>
        class Resource;

        template <typename T>
        class HT_API Handle
        {
        public:
            Handle();
            Handle(const Handle& rhs);
            Handle(Handle&& rhs);
            ~Handle();

            Handle& operator=(const Handle& rhs);
            Handle& operator=(Handle&& rhs);

            T* operator->() const;

            bool operator>(const Handle<T>& rhs) const;
            bool operator<(const Handle<T>& rhs) const;
            bool operator==(const Handle<T>& rhs) const;
            bool operator!=(const Handle<T>& rhs) const;

            template <typename TNew>
            Handle<TNew> StaticCast() const;

            template <typename TNew>
            Handle<TNew> DynamicCast() const;

            bool IsValid() const;

            void Release();

        private:
            friend class Resource<T>;
            template <typename TNew>
            friend class Handle;

            T*              m_data;
            uint32_t*       m_count;
            const uint64_t* m_id;
            mutable std::mutex m_mutex;

            Handle(T* data, uint32_t* count, const uint64_t* id);


        };

        template <typename T>
        class HT_API Resource : public Core::INonCopy
        {
        public:
            Resource() = default;
            Resource(Resource&&) = default;
            virtual ~Resource() = default;

            Resource& operator=(Resource&&) = default;

            template <typename... Args>
            static Handle<T> GetHandle(uint64_t id, Args&&... args);

        protected:
            uint32_t m_count;
            uint64_t m_id;

            Resource(uint64_t id);
        };
    }
}

#include <ht_handle.inl>
#include <ht_resource.inl>

