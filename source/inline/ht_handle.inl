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
        template <typename Type>
        inline Handle<Type>::Handle()
            : m_data(), m_count()
        {

        }

        template <typename Type>
        inline Handle<Type>::Handle(const Handle<Type>& rhs)
            : m_data(rhs.m_data),
              m_count(rhs.m_count)
        {
            if (m_count)
                ++(*m_count);
        }

        template <typename Type>
        inline Handle<Type>::Handle(const Handle<Type>&& rhs)
            : m_data(std::move(rhs.m_data)),
              m_count(std::move(rhs.m_count))
        {
            rhs.m_data = nullptr;
            rhs.m_count = nullptr;
        }

        template <typename Type>
        inline Handle<Type>::Handle(Type* data, uint32_t* count)
            : m_data(std::move(data)),
              m_count(std::move(m_count))
        {
            if (m_count)
                ++(*m_count);
        }

        template <typename Type>
        inline Handle<Type>::~Handle()
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

        template <typename Type>
        inline Handle<Type>& Handle<Type>::operator=(const Handle<Type>& rhs)
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

            return *this;
        }

        template <typename Type>
        inline Handle<Type>& Handle<Type>::operator=(Handle<Type>&& rhs)
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

            rhs.m_data = nullptr;
            rhs.m_count = nullptr;

            return *this;
        }

        template <typename Type>
        inline Type* Handle<Type>::operator->() const
        {
            return m_data;
        }
        
        template <typename Type>
        inline bool Handle<Type>::operator>(const Handle<Type>& rhs) const
        {
            return m_data > rhs.m_data;
        }

        template <typename Type>
        inline bool Handle<Type>::operator<(const Handle<Type>& rhs) const
        {
            return m_data < rhs.m_data;
        }

        template <typename Type>
        inline bool Handle<Type>::operator==(const Handle<Type>& rhs) const
        {
            return m_data == rhs.m_data;
        }

        template <typename Type>
        inline bool Handle<Type>::operator!=(const Handle<Type>& rhs) const
        {
            return m_data != rhs.m_data;
        }

        template <typename Type>
        inline bool Handle<Type>::IsValid() const
        {
            return m_data != nullptr;
        }

        template <typename Type>
        inline void Handle<Type>::Release()
        {
            /**
            * Need to release resource.
            * This could signal to a resource manager
            * to remove it, but this is up for debate.
            */

            m_data = nullptr;
            m_count = nullptr;
        }
    }
}