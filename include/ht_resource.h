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
        class HT_API Resource : public Core::INonCopy
        {
            //static_assert(std::is_base_of<Resource<ResourceType>, ResourceType>::value, "child class of template does not match template type");
        public:
            class Handle
            {
			public:
                Handle(const Handle& rhs);
                Handle(Handle&& rhs);
                ~Handle();
                Handle& operator=(const Handle& rhs);
                Handle& operator=(Handle&& rhs);

                ResourceType* operator->();
            private:
                friend class Resource;
                Handle(ResourceType* ptr);
				ResourceType* m_ptr;
            };

            static Handle GetResourceHandle(const std::string& fileName);
        protected:
            virtual bool VInitFromFile(const std::string& file) = 0;
            //static std::map<std::string, ResourceType*> s_resourceBank;
        private:
            void IncrementRef();
            void DecrementRef();
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