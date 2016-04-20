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

        //Still required for HT_DEBUG_PRINTF
        using namespace Core;

        RenderTarget::RenderTarget(Core::Guid ID) : FileResource(std::move(ID)) {}

        bool RenderTarget::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::RenderTargets) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                Core::JsonExtract<uint32_t>(json, "Width", m_width);
                Core::JsonExtract<uint32_t>(json, "Height", m_height);
                Core::JsonExtract<std::string>(json, "Format", m_format);

                nlohmann::json clearColor = json["ClearColor"];
                if (!clearColor.is_null())
                {
                    for (uint32_t i = 0; i < 4; i++)
                        m_clearColor.push_back(clearColor[i]);
                }

                jsonStream.close();
                return true;
            }
            else
            {
                HT_DEBUG_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderTargets) + fileName);
                return false;
            }
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
        std::vector<float> RenderTarget::GetClearColor() const
        {
            return m_clearColor;
        }
    }
}
