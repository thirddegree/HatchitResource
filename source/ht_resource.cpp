#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        template<typename ResourceType>
        Resource<ResourceType>::Handle Resource<ResourceType>::GetResourceHandle(const FileName& fileName)
        {
            if (s_resourceBank.count(fileName) == 0)
            {
                //File not loaded, load file
                s_resourceBank[fileName] = LoadFromFile(fileName);
            }
            return Resource<ResourceType>::Handle(&s_resourceBank[fileName]);
        }

        template<typename ResourceType>
        ResourceType Resource<ResourceType>::LoadFromFile(const FileName& fileName)
        {
            ResourceType rawResource;
            rawResource.InitFromFile(fileName);
            return rawResource;
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(ResourceType* ptr) : m_ptr(ptr)
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(const Resource<ResourceType>::Handle& rhs) : m_ptr(rhs.m_ptr)
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->IncrementRef();
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::Handle(Resource<ResourceType>::Handle&& rhs) : m_ptr(rhs.m_ptr) {}

        template<typename ResourceType>
        Resource<ResourceType>::Handle::~Handle()
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::operator=(const Resource<ResourceType>::Handle& rhs)
        {
            static_cast<Resource<ResourceType>*>(rhs.m_ptr)->IncrementRef();
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
            m_ptr = rhs.m_ptr;
        }

        template<typename ResourceType>
        Resource<ResourceType>::Handle::operator=(Resource<ResourceType>::Handle&& rhs)
        {
            static_cast<Resource<ResourceType>*>(m_ptr)->DecrementRef(m_fileName);
            m_ptr = rhs.m_ptr;
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
        void Resource<ResourceType>::DecrementRef(const FileName& key)
        {
            m_refCount--;
            if (m_refCount == 0)
            {
                s_resourceBank.erase(key);
            }
        }
    }
}