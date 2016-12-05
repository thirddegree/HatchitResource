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
#include <utility>

namespace Hatchit
{
    namespace Resource
    {
        template <typename T>
        inline Handle<T>::Handle()
            : m_data(), m_count(), m_id()
        {

        }

        template <typename T>
        inline Handle<T>::Handle(const Handle<T>& rhs)
            : m_data(rhs.m_data),
              m_count(rhs.m_count),
              m_id(rhs.m_id)
        {
            if (m_count)
                ++(*m_count);
        }

        template <typename T>
        inline Handle<T>::Handle(Handle<T>&& rhs)
            : m_data(std::move(rhs.m_data)),
              m_count(std::move(rhs.m_count)),
              m_id(std::move(rhs.m_id))
        {
            rhs.m_data = nullptr;
            rhs.m_count = nullptr;
            rhs.m_id = nullptr;
        }

        template <typename T>
        inline Handle<T>::Handle(T* data, uint32_t* count, const uint64_t* id)
            : m_data(std::move(data)),
              m_count(std::move(m_count)),
              m_id(std::move(id))
        {
            if (m_count)
                ++(*m_count);
        }

        template <typename T>
        inline Handle<T>::~Handle()
        {
            if (m_count && !--(*m_count))
            {
                /**
                * Need to release resource.
                * This could signal to a resource manager
                * to remove it, but this is up for debate.
                */
            }
        }

        template <typename T>
        inline Handle<T>& Handle<T>::operator=(const Handle<T>& rhs)
        {
            if (rhs.m_count)
                ++(*rhs.m_count);

            if (m_count && !--(*m_count))
            {
                /**
                * Need to release resource.
                * This could signal to a resource manager
                * to remove it, but this is up for debate.
                */
            }

            m_data = rhs.m_data;
            m_count = rhs.m_count;
            m_id = rhs.m_id;

            return *this;
        }

        template <typename T>
        inline Handle<T>& Handle<T>::operator=(Handle<T>&& rhs)
        {
            if (m_count && --(*m_count))
            {
                /**
                * Need to release resource.
                * This could signal to a resource manager
                * to remove it, but this is up for debate.
                */
            }

            m_data = std::move(rhs.m_data);
            m_count = std::move(rhs.m_count);
            m_id = std::move(rhs.m_id);

            rhs.m_data = nullptr;
            rhs.m_count = nullptr;
            rhs.m_id = nullptr;

            return *this;
        }

        template <typename T>
        inline T* Handle<T>::operator->() const
        {
            return m_data;
        }
        
        template <typename T>
        inline bool Handle<T>::operator>(const Handle<T>& rhs) const
        {
            return m_data > rhs.m_data;
        }

        template <typename T>
        inline bool Handle<T>::operator<(const Handle<T>& rhs) const
        {
            return m_data < rhs.m_data;
        }

        template <typename T>
        inline bool Handle<T>::operator==(const Handle<T>& rhs) const
        {
            return m_data == rhs.m_data;
        }

        template <typename T>
        inline bool Handle<T>::operator!=(const Handle<T>& rhs) const
        {
            return m_data != rhs.m_data;
        }

        template<typename T>
        template <typename TNew>
        inline Handle<TNew> Handle<T>::StaticCast() const
        {
            TNew* _new = static_cast<TNew*>(m_data);

            return Handle<TNew>(_new, m_count, m_id);
        }

        template <typename T>
        template <typename TNew>
        inline Handle<TNew> Handle<T>::DynamicCast() const
        {
            TNew* _new = dynamic_cast<TNew*>(m_data);
            if (_new)
            {
                return Handle<TNew>(_new, m_count, m_id);
            }
            else
            {
                return Handle<TNew>();
            }
        }

        template <typename T>
        inline bool Handle<T>::IsValid() const
        {
            return m_data != nullptr;
        }

        template <typename T>
        inline void Handle<T>::Release()
        {
            /**
            * Need to release resource.
            * This could signal to a resource manager
            * to remove it, but this is up for debate.
            */

            m_data = nullptr;
            m_count = nullptr;
            m_id = nullptr;
        }
    }
}