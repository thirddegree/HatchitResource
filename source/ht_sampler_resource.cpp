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

        MutableSampler::MutableSampler(std::string ID) : FileResource<MutableSampler>(std::move(ID)) {}

        bool MutableSampler::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::Samplers) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                //Parse Filter
                auto filter = json["Filter"];
                std::string minFilter;
                std::string magFilter;
                JsonExtractString(filter, "Mag", magFilter);
                JsonExtractString(filter, "Min", minFilter);
                m_filter.mag = SamplerFilterModeFromString(magFilter);
                m_filter.min = SamplerFilterModeFromString(minFilter);

                //Parse Address
                auto address = json["Address"];
                std::string uMode;
                std::string vMode;
                std::string wMode;
                JsonExtractString(address, "U", uMode);
                JsonExtractString(address, "V", vMode);
                JsonExtractString(address, "W", wMode);
                m_address.u = SamplerAddressModeFromString(uMode);
                m_address.v = SamplerAddressModeFromString(vMode);
                m_address.w = SamplerAddressModeFromString(wMode);


                std::string mipMode;
                JsonExtractString(json, "MipMode", mipMode);
                m_mipMode = SamplerMipModeFromString(mipMode);

                JsonExtractFloat(json, "MipLODBias", m_mipLODBias);
                JsonExtractFloat(json, "MinLOD", m_minLOD);
                JsonExtractFloat(json, "MaxLOD", m_maxLOD);
                JsonExtractUint32(json, "MaxAnisotropy", m_maxAnisotropy);

                std::string compareOp;
                JsonExtractString(json, "CompareOp", compareOp);
                m_compareOp = SamplerCompareOpFromString(compareOp);

                std::string borderColor;
                JsonExtractString(json, "BorderColor", borderColor);
                m_borderColor = SamplerBorderColorFromString(borderColor);

                std::string colorSpace;
                JsonExtractString(json, "ColorSpace", colorSpace);
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


