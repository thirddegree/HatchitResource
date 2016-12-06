/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_texture_resource.h>
#include <ht_file.h>
#include <ht_file_exception.h>
#include <ht_image.h>

namespace Hatchit
{
    namespace Resource
    {
        Texture::Texture(uint64_t id)
            : FileResource<Texture>(std::move(id))
        {

        }

        bool Texture::Initialize(const std::string &path)
        {
            using namespace Core;

            File f;
            try {

                f.Open(path, File::FileMode::ReadBinary);

                auto image = Image::Load(f, Image::Channels::AUTO);

                m_width = image->GetWidth();
                m_height = image->GetHeight();
                m_mips = 1;
                m_bpp = static_cast<uint8_t>(image->GetBPP());
                m_channels = static_cast<uint32_t>(image->GetChannels());

                m_data = new BYTE[m_width * m_height];
                std::memcpy(reinterpret_cast<void*>(m_data), image->GetData(), m_width*m_height);
            }
            catch(const FileException& e)
            {
                HT_DEBUG_PRINTF("%s\n", e.what());
                return false;
            }

            return true;
        }
    }
}