#pragma once

#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        typename Resource<ResourceType>::Handle Resource<ResourceType>::GetResourceHandle(const std::string& fileName)
        {
            if (s_resourceBank.count(fileName) == 0)
            {
                //File not loaded, load file
                s_resourceBank[fileName] = LoadFromFile(fileName);
            }
            return Resource<ResourceType>::Handle(&s_resourceBank[fileName], fileName);
        }

        template<typename ResourceType>
        ResourceType Resource<ResourceType>::LoadFromFile(const std::string& fileName)
        {
            ResourceType rawResource;
            File file;

            file.Open(Core::os_exec_dir() + fileName, FileMode::ReadText);
            rawResource.VInitFromFile(&file);
            return rawResource;
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(ResourceType* ptr, std::string fileName) : m_ptr(ptr), m_fileName(std::move(fileName))
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(const Handle& rhs) : m_ptr(rhs.m_ptr), m_fileName(rhs.m_fileName)
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(Handle&& rhs) : m_ptr(rhs.m_ptr), m_fileName(rhs.m_fileName) {}

        template<typename ResourceType>
        Resource<ResourceType>::Handle::~Handle()
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
        }

        template<typename ResourceType>
        typename Resource<ResourceType>::Handle& Resource<ResourceType>::Handle::operator=(const Handle& rhs)
        {
            static_cast<Resource<ResourceType>*>(rhs.m_ptr)->IncrementRef();
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
            m_ptr = rhs.m_ptr;
            m_fileName = rhs.m_fileName;
            return *this;
        }

        template<typename ResourceType>
        typename Resource<ResourceType>::Handle& Resource<ResourceType>::Handle::operator=(Handle&& rhs)
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
            m_ptr = rhs.m_ptr;
            m_fileName = rhs.m_fileName;
            return *this;
        }

        template<typename ResourceType>
        ResourceType* Resource<ResourceType>::Handle::operator->()
        {
            return m_ptr;
        }

        template<typename ResourceType>
        void Resource<ResourceType>::IncrementRef()
        {
            m_refCount++;
        }

        template<typename ResourceType>
        void Resource<ResourceType>::DecrementRef(const std::string& key)
        {
            m_refCount--;
            if (m_refCount == 0)
            {
                s_resourceBank.erase(key);
            }
        }
    }
}