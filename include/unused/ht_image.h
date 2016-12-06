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

#pragma once

#include <ht_platform.h>
#include <ht_types.h>
#include <ht_file.h>

namespace Hatchit {

    namespace Resource {

        class HT_API Image
        {
        public:
            Image();

            ~Image();

            const int32_t GetWidth()   const;
            const int32_t GetHeight()  const;
            const int32_t GetChannels() const;
            const int32_t GetBPP() const;
            const BYTE*   GetData()    const;


            enum class Channels
            {
                AUTO,
                L,
                LA,
                RGB,
                RGBA
            };

            static Image* Load(Core::File& file, Channels channels);


        private:
            int32_t m_width;
            int32_t m_height;
            int32_t m_channels;
            int32_t m_bpp;
            BYTE*   m_data;
        };
    }

}
