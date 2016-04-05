#pragma once

#include <ht_resource.h>
#include <ht_resourcemanager.h>
#include <cassert>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        Handle<ResourceType>::Handle()
            : m_ptr(),
            m_refCount(),
            m_mapKey() {}

        template<typename ResourceType>
        Handle<ResourceType>::Handle(ResourceType* ptr, uint32_t* refCounter, const std::string* mapKey) 
            : m_ptr(ptr),
            m_refCount(refCounter),
            m_mapKey(mapKey)
        {
            if(m_refCount)
                ++(*m_refCount);
        }

        template<typename ResourceType>
        Handle<ResourceType>::Handle(const Handle& rhs) 
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_mapKey(rhs.m_mapKey)
        {
            if(m_refCount)
                ++(*m_refCount);
        }

        template<typename ResourceType>
        Handle<ResourceType>::Handle(Handle&& rhs) 
            : m_ptr(rhs.m_ptr),
            m_refCount(rhs.m_refCount),
            m_mapKey(rhs.m_mapKey) {}

        template<typename ResourceType>
        Handle<ResourceType>::~Handle()
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete here
                ResourceManager::ReleaseRawPointer<ResourceType>(*m_mapKey);
                m_ptr = nullptr;
                m_refCount = nullptr;
                m_mapKey = nullptr;
            }
        }

        template<typename ResourceType>
        Handle<ResourceType>& Handle<ResourceType>::operator=(const Handle& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete here
                ResourceManager::ReleaseRawPointer<ResourceType>(*m_mapKey);
                m_ptr = nullptr;
                m_refCount = nullptr;
                m_mapKey = nullptr;
            }
            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            m_mapKey = rhs.m_mapKey;
            if (m_refCount)
                ++m_refCount;

            return *this;
        }

        template<typename ResourceType>
        Handle<ResourceType>& Handle<ResourceType>::operator=(Handle&& rhs)
        {
            if (m_refCount && !--(*m_refCount))
            {
                //Delete here
            }
            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            m_mapKey = rhs.m_mapKey;

            return *this;
        }

        template<typename ResourceType>
        const ResourceType* Handle<ResourceType>::operator->() const
        {
            return m_ptr;
        }

        template<typename ResourceType>
        template<typename NewResourceType>
        Handle<NewResourceType> Handle<ResourceType>::CastHandle()
        {
            NewResourceType* nrt = dynamic_cast<NewResourceType*>(m_ptr);
            return Handle<NewResourceType>(nrt, m_refCount, m_mapKey);
        }

        template<typename ResourceType>
        bool Handle<ResourceType>::IsValid() const
        {
            return m_ptr != nullptr;
        }

        template<typename ResourceType>
        Resource<ResourceType>::Resource(std::string fileName) : m_refCount(0), m_fileName(std::move(fileName)) {};

        template<typename ResourceType>
        Handle<ResourceType> Resource<ResourceType>::GetResourceHandle(const std::string& fileName)
        {
            ResourceType* resource = ResourceManager::GetRawPointer<ResourceType>(fileName);
            if (resource)
                return Handle<ResourceType>(resource, &(resource->m_refCount), &(resource->m_fileName));
            else
                return Handle<ResourceType>();
        }
    }
}