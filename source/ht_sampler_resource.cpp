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
		//using namespace Core;

        MutableSampler::MutableSampler(Core::Guid ID) : FileResource<MutableSampler>(std::move(ID)) {}

        bool MutableSampler::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::Samplers) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                //Parse Filter
                auto filter = json["Filter"];
                std::string minFilter;
                std::string magFilter;
                Core::JsonExtract<std::string>(filter, "Mag", magFilter);
                Core::JsonExtract<std::string>(filter, "Min", minFilter);
                m_filter.mag = SamplerFilterModeFromString(magFilter);
                m_filter.min = SamplerFilterModeFromString(minFilter);

                //Parse Address
                auto address = json["Address"];
                std::string uMode;
                std::string vMode;
                std::string wMode;
                Core::JsonExtract<std::string>(address, "U", uMode);
                Core::JsonExtract<std::string>(address, "V", vMode);
                Core::JsonExtract<std::string>(address, "W", wMode);
                m_address.u = SamplerAddressModeFromString(uMode);
                m_address.v = SamplerAddressModeFromString(vMode);
                m_address.w = SamplerAddressModeFromString(wMode);


                std::string mipMode;
                Core::JsonExtract<std::string>(json, "MipMode", mipMode);
                m_mipMode = SamplerMipModeFromString(mipMode);

                Core::JsonExtract<float>(json, "MipLODBias", m_mipLODBias);
                Core::JsonExtract<float>(json, "MinLOD", m_minLOD);
                Core::JsonExtract<float>(json, "MaxLOD", m_maxLOD);
                Core::JsonExtract<uint32_t>(json, "MaxAnisotropy", m_maxAnisotropy);

                std::string compareOp;
                Core::JsonExtract<std::string>(json, "CompareOp", compareOp);
                m_compareOp = SamplerCompareOpFromString(compareOp);

                std::string borderColor;
                Core::JsonExtract<std::string>(json, "BorderColor", borderColor);
                m_borderColor = SamplerBorderColorFromString(borderColor);

                std::string colorSpace;
                Core::JsonExtract<std::string>(json, "ColorSpace", colorSpace);
                m_colorSpace = SamplerColorSpaceFromString(colorSpace);

                jsonStream.close();
            }
            else
            {
                return false;
            }
           return true;
        }
    }
}


