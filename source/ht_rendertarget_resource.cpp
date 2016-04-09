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

#include <ht_rendertarget_resource.h>
#include <ht_debug.h>

namespace Hatchit {

    namespace Resource {

        using namespace Core;

        RenderTarget::RenderTarget(std::string ID) : FileResource(std::move(ID)) {}

        bool RenderTarget::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::RenderTargets) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                JsonExtractUint32(json, "Width", m_width);
                JsonExtractUint32(json, "Height", m_height);
                JsonExtractString(json, "Format", m_format);

                jsonStream.close();
                return true;
            }
            else
            {
                HT_DEBUG_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderTargets) + fileName);
                return false;
            }
        }

        bool RenderTarget::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::RenderTargets) + filename);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                JsonExtractUint32(json, "Width", m_width);
                JsonExtractUint32(json, "Height", m_height);
                JsonExtractString(json, "Format", m_format);

                jsonStream.close();
                return true;
            }

            HT_DEBUG_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderTargets) + filename);

            return false;
        }

        uint32_t RenderTarget::GetWidth() const 
        {
            return m_width;
        }
        uint32_t RenderTarget::GetHeight() const
        {
            return m_height;
        }
        std::string RenderTarget::GetFormat() const
        {
            return m_format;
        }
    }
}
