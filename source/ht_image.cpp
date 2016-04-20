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

#include <ht_image.h>
#include <stb_image.h>

namespace Hatchit {

    namespace Resource {

        Image::Image()
        {
            m_width = 0;
            m_height = 0;
            m_channels = 0;
            m_data = nullptr;
        }

        Image::~Image()
        {
            stbi_image_free(m_data);
        }

        const int32_t Image::GetWidth() const
        {
            return m_width;
        }

        const int32_t Image::GetHeight() const
        {
            return m_height;
        }

        const int32_t Image::GetChannels() const
        {
            return m_channels;
        }

        const int32_t Image::GetBPP() const
        {
            return m_bpp;
        }

        const BYTE* Image::GetData() const
        {
            return m_data;
        }

        static int FileEOFCallback(void* file)
        {
            return static_cast<Core::File*>(file)->Handle()->eof();
        }

        static int FileReadCallback(void* file, char* data, int size)
        {
            return static_cast<Core::File*>(file)->Read(reinterpret_cast<BYTE*>(data), static_cast<size_t>(size));
        }

        static void FileSkipCallback(void* file, int n)
        {
            static_cast<Core::File*>(file)->Seek(n, Core::File::FileSeek::Current);
        }

        ////////////////////////////////////////////////
        // Bitmap static functions
        ////////////////////////////////////////////////

        Image* Image::Load(Core::File* file, Channels channels)
        {
            Image* bitmap = new Image;

            int req_channels = 0;
            switch (channels)
            {
            case Channels::AUTO:
                req_channels = 0;
                break;
            case Channels::L:
                req_channels = 1;
                bitmap->m_bpp = 32;
                break;
            case Channels::LA:
                req_channels = 2;
                bitmap->m_bpp = 32;
                break;
            case Channels::RGB:
                req_channels = 3;
                bitmap->m_bpp = 32;
                break;
            case Channels::RGBA:
                req_channels = 4;
                bitmap->m_bpp = 32;
                break;

            default:
                break;
            }

            stbi_io_callbacks callbacks;
            callbacks.eof = FileEOFCallback;
            callbacks.read = FileReadCallback;
            callbacks.skip = FileSkipCallback;

            bitmap->m_data = stbi_load_from_callbacks(&callbacks, file,
                &bitmap->m_width, &bitmap->m_height, &bitmap->m_channels,
                req_channels);
            if (channels == Channels::AUTO)
                bitmap->m_bpp = bitmap->m_channels * 8;

            return bitmap;
        }
    }

}
