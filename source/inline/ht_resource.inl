#pragma once

#include <ht_resource.h>
#include <ht_resourcemanager.h>
#include <cassert>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        typename Resource<ResourceType>::Handle Resource<ResourceType>::GetResourceHandle(const std::string& fileName)
        {
			ResourceType* resource = ResourceManager::GetRawPointer<ResourceType>(fileName);

			return Resource<ResourceType>::Handle(resource);
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(ResourceType* ptr) : m_ptr(ptr)
        {
			if(m_ptr)
				static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(const Handle& rhs) : m_ptr(rhs.m_ptr)
        {
			if(m_ptr)
				static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(Handle&& rhs) : m_ptr(rhs.m_ptr) {}

        template<typename ResourceType>
        Resource<ResourceType>::Handle::~Handle()
        {
			if(m_ptr)
				static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef();
        }

        template<typename ResourceType>
        typename Resource<ResourceType>::Handle& Resource<ResourceType>::Handle::operator=(const Handle& rhs)
        {
			if(rhs.m_ptr)
				static_cast<Resource<ResourceType>*>(rhs.m_ptr)->IncrementRef();
			if(m_ptr)
				static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef();
            m_ptr = rhs.m_ptr;
            return *this;
        }

        template<typename ResourceType>
        typename Resource<ResourceType>::Handle& Resource<ResourceType>::Handle::operator=(Handle&& rhs)
        {
			if(m_ptr)
				static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef();
            m_ptr = rhs.m_ptr;
            return *this;
        }

        template<typename ResourceType>
        ResourceType* Resource<ResourceType>::Handle::operator->()
        {
            return m_ptr;
        }
        template<typename ResourceType>
        const ResourceType* Resource<ResourceType>::Handle::operator->() const
        {
            return m_ptr;
        }

		template<typename ResourceType>
		Resource<ResourceType>::Resource(std::string fileName) : m_refCount(0), m_fileName(std::move(fileName)) {};

        template<typename ResourceType>
        void Resource<ResourceType>::IncrementRef()
        {
            m_refCount++;
        }

        template<typename ResourceType>
        void Resource<ResourceType>::DecrementRef()
        {
            m_refCount--;
            if (m_refCount == 0)
               ResourceManager::ReleaseRawPointer<ResourceType>(m_fileName);
        }
    }
}