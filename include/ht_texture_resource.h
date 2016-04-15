/**
**    Hatchit Engine
<<<<<<< Updated upstream
**    Copyright(c) 2015 Third-Degree
=======
**    Copyright(c) 2015-2016 ThirdDegree
>>>>>>> Stashed changes
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
        class HT_API Texture : public FileResource<Texture>
        {
        public:
            Texture(std::string ID);
            virtual ~Texture() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

            bool VInitFromFile(const std::string& file);

            uint32_t GetWidth() const;
            uint32_t GetHeight() const;

            uint8_t GetBPP() const;

            uint32_t GetMIPLevels() const;

            uint8_t GetChannels() const;

            const BYTE* GetData() const;

        private:
            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_mipLevels;
            uint8_t m_bpp;
            uint8_t m_channels;

            const BYTE* m_data;
        };

        using TextureHandle = Core::Handle<const Texture>;
    }
}