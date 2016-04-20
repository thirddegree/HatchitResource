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

namespace Hatchit {

    namespace Resource {

        class HT_API RenderTarget : public FileResource<RenderTarget>
        {
        public:
            RenderTarget(Core::Guid ID);
            virtual ~RenderTarget() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

            uint32_t GetWidth() const;
            uint32_t GetHeight() const;
            std::string GetFormat() const;
            std::vector<float> GetClearColor() const;

        private:
            uint32_t m_width;
            uint32_t m_height;
            std::string m_format;
            std::vector<float> m_clearColor;
        };

        using RenderTargetHandle = Core::Handle<const RenderTarget>;
    }
}