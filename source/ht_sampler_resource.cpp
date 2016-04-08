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

#include <json.hpp>
#include <ht_sampler_resource.h>
#include <ht_path_singleton.h>

#include <algorithm>

namespace Hatchit
{
    namespace Resource
    {
		using namespace Core;

        Sampler::Sampler(std::string ID, const std::string& fileName) : FileResource<Sampler>(std::move(ID))
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::Samplers) + fileName);

            std::string filterModeString;
            std::string wrapModeString;
            std::string colorSpaceString;

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                JsonExtractString(json, "FilterMode", filterModeString);
                JsonExtractString(json, "WrapMode", wrapModeString);
                JsonExtractString(json, "ColorSpace", colorSpaceString);

                jsonStream.close();
            }
            else
            {
                return;
            }

            //Make everything upper case
            std::transform(filterModeString.begin(), filterModeString.end(), filterModeString.begin(), ::toupper);
            std::transform(wrapModeString.begin(), wrapModeString.end(), wrapModeString.begin(), ::toupper);
            std::transform(colorSpaceString.begin(), colorSpaceString.end(), colorSpaceString.begin(), ::toupper);

            if (filterModeString == "BILINEAR")
                m_filterMode = Sampler::FilterMode::BILINEAR;
            else if (filterModeString == "NEAREST")
                m_filterMode = Sampler::FilterMode::NEAREST;
            else
                m_filterMode = Sampler::FilterMode::BILINEAR;

            if (wrapModeString == "WRAP")
                m_wrapMode = Sampler::WrapMode::WRAP;
            else if (wrapModeString == "CLAMP")
                m_wrapMode = Sampler::WrapMode::CLAMP;
            else if (wrapModeString == "BORDER")
                m_wrapMode = Sampler::WrapMode::BORDER;
            else if (wrapModeString == "MIRROR")
                m_wrapMode = Sampler::WrapMode::MIRROR;
            else if (wrapModeString == "MIRROR_ONCE")
                m_wrapMode = Sampler::WrapMode::MIRROR_ONCE;
            else
                m_wrapMode = Sampler::WrapMode::WRAP;

            if (colorSpaceString == "LINEAR")
                m_colorSpace = Sampler::ColorSpace::LINEAR;
            else if (colorSpaceString == "GAMMA")
                m_colorSpace = Sampler::ColorSpace::GAMMA;
            else
                m_colorSpace = Sampler::ColorSpace::LINEAR;
		}

        bool Sampler::VInitFromFile(const std::string & filename)
        {
			nlohmann::json json;
			std::ifstream jsonStream(Path::Value(Path::Directory::Samplers) + filename);

			std::string filterModeString;
			std::string wrapModeString;
			std::string colorSpaceString;

			if (jsonStream.is_open())
			{
				jsonStream >> json;

				JsonExtractString(json, "FilterMode", filterModeString);
				JsonExtractString(json, "WrapMode", wrapModeString);
				JsonExtractString(json, "ColorSpace", colorSpaceString);

				jsonStream.close();
			}
			else
			{
				return false;
			}

			//Make everything upper case
			std::transform(filterModeString.begin(), filterModeString.end(), filterModeString.begin(), ::toupper);
			std::transform(wrapModeString.begin(), wrapModeString.end(), wrapModeString.begin(), ::toupper);
			std::transform(colorSpaceString.begin(), colorSpaceString.end(), colorSpaceString.begin(), ::toupper);

			if (filterModeString == "BILINEAR")
				m_filterMode = Sampler::FilterMode::BILINEAR;
			else if (filterModeString == "NEAREST")
				m_filterMode = Sampler::FilterMode::NEAREST;
			else
				m_filterMode = Sampler::FilterMode::BILINEAR;

			if (wrapModeString == "WRAP")
				m_wrapMode = Sampler::WrapMode::WRAP;
			else if (wrapModeString == "CLAMP")
				m_wrapMode = Sampler::WrapMode::CLAMP;
			else if (wrapModeString == "BORDER")
				m_wrapMode = Sampler::WrapMode::BORDER;
			else if (wrapModeString == "MIRROR")
				m_wrapMode = Sampler::WrapMode::MIRROR;
			else if (wrapModeString == "MIRROR_ONCE")
				m_wrapMode = Sampler::WrapMode::MIRROR_ONCE;
			else
				m_wrapMode = Sampler::WrapMode::WRAP;

			if (colorSpaceString == "LINEAR")
				m_colorSpace = Sampler::ColorSpace::LINEAR;
			else if (colorSpaceString == "GAMMA")
				m_colorSpace = Sampler::ColorSpace::GAMMA;
			else
				m_colorSpace = Sampler::ColorSpace::LINEAR;

            return true;
        }

        Sampler::FilterMode Sampler::GetFilterMode() const { return m_filterMode; }
        Sampler::WrapMode Sampler::GetWrapMode() const { return m_wrapMode; }
        Sampler::ColorSpace Sampler::GetColorSpace() const { return m_colorSpace; }
    }
}


