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

#include <ht_bitmap.h>
#include <stb_image.h>

namespace Hatchit {

    namespace Image {

        Bitmap::Bitmap()
        {
            m_width = 0;
            m_height = 0;
            m_channels = 0;
            m_data = nullptr;
        }

        Bitmap::~Bitmap()
        {
            stbi_image_free(m_data);
        }

        const int32_t Bitmap::GetWidth() const
        {
            return m_width;
        }

        const int32_t Bitmap::GetHeight() const
        {
            return m_height;
        }

        const int32_t Bitmap::GetChannels() const
        {
            return m_channels;
        }

        const BYTE* Bitmap::GetData() const
        {
            return m_data;
        }

        ////////////////////////////////////////////////
        // Bitmap static functions
        ////////////////////////////////////////////////

        Bitmap* Bitmap::Load(Core::File* file, Channels channels)
        {
            Bitmap* bitmap = new Bitmap;

            int req_channels = 0;
            switch (channels)
            {
            case Channels::AUTO:
                req_channels = 0;
                break;
            case Channels::L:
                req_channels = 1;
                break;
            case Channels::LA:
                req_channels = 2;
                break;
            case Channels::RGB:
                req_channels = 3;
                break;
            case Channels::RGBA:
                req_channels = 4;
                break;

            default:
                break;
            }
            bitmap->m_data = stbi_load_from_file(file->Handle(),
                &bitmap->m_width, &bitmap->m_height, &bitmap->m_channels,
                req_channels);

            return bitmap;
        }
    }

}
