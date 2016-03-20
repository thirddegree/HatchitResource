#pragma once

#include <ht_platform.h>
#include <ht_noncopy.h>
#include <ht_file.h>
#include <map>
#include <type_traits>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        class HT_API Resource : public Core::INonCopy
        {
            static_assert(std::is_base_of<Resource<ResourceType>, ResourceType>::value);
        public:
            class Handle
            {
                Handle(const Handle& rhs);
                Handle(Handle&& rhs);
                ~Handle();
                Handle& operator=(const Handle& rhs);
                Handle& operator=(Handle&& rhs);

                ResourceType* operator->();
            private:
                friend class Resource;
                Handle(ResourceType* ptr, std::string fileName);

                ResourceType* m_ptr;
                std::string m_fileName;
            };

            static Handle GetResourceHandle(const std::string& fileName);
        protected:
            virtual void InitFromFile(const std::string& file) = 0;
            static std::map<std::string, ResourceType> s_resourceBank;
            static ResourceType LoadFromFile(const std::string& fileName);
        private:
            void IncrementRef();
            void DecrementRef(const std::string& key);
            uint32_t m_refCount;
        };
    }
}

/*
    Here's how the classes are going to be structured for resources:
    Resource<T> is the base class for all resources that have to be loaded / generated
    T is going to be the actual implementation of the data.
    Then we create a TPtr alias that is equivalent to Resource<T>::Handle
*/

#include <ht_resource.inl>