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

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Sampler : public FileResource<Sampler>
        {
        public:
            //Enums
            enum WrapMode
            {
				WRAP,
                CLAMP,
				BORDER,
				MIRROR,
				MIRROR_ONCE
            };

            enum FilterMode
            {
                NEAREST,
                BILINEAR
            };

            enum ColorSpace
            {
                GAMMA,
                LINEAR
            };

            Sampler(std::string name);
            virtual ~Sampler() = default;

            // Inherited via Resource
            virtual bool VInitFromFile(const std::string & file) override;

            FilterMode GetFilterMode() const;
            WrapMode GetWrapMode() const;
            ColorSpace GetColorSpace() const;

        private:
            FilterMode m_filterMode;
            WrapMode m_wrapMode;
            ColorSpace m_colorSpace;
        };

        using SamplerHandle = Core::Handle<const Sampler>;
    }
}