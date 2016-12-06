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