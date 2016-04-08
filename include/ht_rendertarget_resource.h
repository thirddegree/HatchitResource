/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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
            RenderTarget(std::string ID);
            virtual ~RenderTarget() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

            virtual bool VInitFromFile(const std::string& filename);

            uint32_t GetWidth() const;
            uint32_t GetHeight() const;
            std::string GetFormat() const;

        private:
            uint32_t m_width;
            uint32_t m_height;
            std::string m_format;
        };

        using RenderTargetHandle = Core::Handle<const RenderTarget>;
    }
}