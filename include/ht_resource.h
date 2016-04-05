#pragma once

#include <ht_platform.h>
#include <ht_noncopy.h>
#include <ht_singleton.h>
#include <ht_file.h>
#include <map>
#include <type_traits>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        class Resource;

        template<typename ResourceType>
        class HT_API Handle
        {
        public:
            Handle();
            Handle(const Handle& rhs);
            Handle(Handle&& rhs);
            ~Handle();
            Handle& operator=(const Handle& rhs);
            Handle& operator=(Handle&& rhs);

            const ResourceType* operator->() const;

            template<typename NewResourceType>
            Handle<NewResourceType> CastHandle();

            bool IsValid() const;
        private:
            friend class Resource<ResourceType>;
            Handle(ResourceType* resource, uint32_t* refCounter, const std::string* m_mapKey);
            ResourceType* m_ptr;
            uint32_t* m_refCount;
            const std::string* m_mapKey;
        };

        template<typename ResourceType>
        class HT_API Resource : public Core::INonCopy
        {
        public:
            virtual ~Resource() { };

            static Handle<ResourceType> GetResourceHandle(const std::string& fileName);
        protected:
            Resource(std::string fileName);
            virtual bool VInitFromFile(const std::string& file) = 0;
        private:
            uint32_t m_refCount;
            std::string m_fileName;
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