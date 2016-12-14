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

#include <ht_fileresource.h>
#include <ht_hash.h>
#include <tuple>

namespace Hatchit
{
    namespace Resource
    {
        template <typename T>
        FileResource<T>::FileResource(uint64_t id)
            : Resource<T>(std::move(id))
        {

        }

        template <typename T>
        template <typename... Args>
        Handle<const T> FileResource<T>::GetHandle(Args&&... args)
        {
            using namespace Core;

            /**
             * We need to retrieve a resource handle using
             * the file path. This means we must convert this path value,
             * to a unique identifier. (or in future we change this signature to take both
             * the identifier and path)
             *
             * First, we must access the path from the variable arguments. Since, the resource classes
             * can generally take any number of arguments. It is dependent on the programmer
             * to know that for FileResource types the PATH of the file MUST be the first argument.
             *
             * NOTE:
             *      This requirement should be explained thoroughly and we should
             *      look to find a way to enforce this requirement as more resource classes
             *      are created.
            */

            /**
             * Accessing Path:
             *      Convert arguments to tuple and use get<T> accessor to
             *      retrieve the first element in tuple -> path
             */
            auto tuple = std::make_tuple(args...);
            auto path =  std::get<0>(tuple);



            uint64_t id = Hash::FNV1A(path);
            Handle<T> handle = Resource<T>::GetHandle(id, std::forward<Args>(args...)...);
            if (handle.IsValid())
            {
                //If the returned handle is valid.
                //We will cast to the corresponding resource type and return.
                return handle.template StaticCast<const T>();
            }
            else
                return Handle<const T>();
        }
    }
}