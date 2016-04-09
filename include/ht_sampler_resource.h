/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 ThirdDegree
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
#include <ht_sampler_base.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API MutableSampler : public FileResource<MutableSampler>, public Sampler
        {
        public:
            MutableSampler(std::string ID);
            virtual ~MutableSampler() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

        private:

            friend class RootLayout;
        };

        using SamplerHandle = Core::Handle<const MutableSampler>;
    }
}