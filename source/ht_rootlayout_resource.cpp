/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 ThirdDegree
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

#include <ht_rootlayout_resource.h>
#include <ht_debug.h>
#include <algorithm>
#include <json.hpp>

namespace Hatchit
{
    namespace Resource
    {
        //using namespace Core;

		RootLayout::RootLayout(Core::Guid ID)
            : FileResource<RootLayout>(std::move(ID)) {}

        bool RootLayout::Initialize(const std::string& fileName)
        {
            nlohmann::json json;

            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::Assets) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                Core::JsonExtract<uint32_t>(json, "ParameterCount", m_parameterCount);

                nlohmann::json flags = json["Flags"];
                for (auto flag : flags)
                {
                    m_flags |= FlagFromString(flag);
                }

                nlohmann::json samplers = json["Samplers"];
                for (auto sampler : samplers)
                {
                    Sampler _sampler;

                    //Parse Filter
                    auto filter = sampler["Filter"];
                    std::string minFilter;
                    std::string magFilter;
                    Core::JsonExtract<std::string>(filter, "Mag", magFilter);
                    Core::JsonExtract<std::string>(filter, "Min", minFilter);
                    _sampler.m_filter.mag = Sampler::SamplerFilterModeFromString(magFilter);
                    _sampler.m_filter.min = Sampler::SamplerFilterModeFromString(minFilter);

                    //Parse Address
                    auto address = sampler["Address"];
                    std::string uMode;
                    std::string vMode;
                    std::string wMode;
                    Core::JsonExtract<std::string>(address, "U", uMode);
                    Core::JsonExtract<std::string>(address, "V", vMode);
                    Core::JsonExtract<std::string>(address, "W", wMode);
                    _sampler.m_address.u = Sampler::SamplerAddressModeFromString(uMode);
                    _sampler.m_address.v = Sampler::SamplerAddressModeFromString(vMode);
                    _sampler.m_address.w = Sampler::SamplerAddressModeFromString(wMode);

                    std::string mipMode;
                    Core::JsonExtract<std::string>(sampler, "MipMode", mipMode);
                    _sampler.m_mipMode = Sampler::SamplerMipModeFromString(mipMode);

                    Core::JsonExtract<float>(sampler, "MipLODBias", _sampler.m_mipLODBias);
                    Core::JsonExtract<float>(sampler, "MinLOD", _sampler.m_minLOD);
                    Core::JsonExtract<float>(sampler, "MaxLOD", _sampler.m_maxLOD);
                    Core::JsonExtract<uint32_t>(sampler, "MaxAnisotropy", _sampler.m_maxAnisotropy);

                    std::string compareOp;
                    Core::JsonExtract<std::string>(sampler, "CompareOp", compareOp);
                    _sampler.m_compareOp = Sampler::SamplerCompareOpFromString(compareOp);

                    std::string borderColor;
                    Core::JsonExtract<std::string>(sampler, "BorderColor", borderColor);
                    _sampler.m_borderColor = Sampler::SamplerBorderColorFromString(borderColor);


                    /*Attempt to find Immutable struct*/
                    if (sampler.find("Immutable") != sampler.end())
                    {
                        //If found, we should load immutable information
                        auto immutable = sampler["Immutable"];

                        Core::JsonExtract<uint32_t>(immutable, "Register", _sampler.m_immutable.shaderRegister);
                        Core::JsonExtract<uint32_t>(immutable, "Space", _sampler.m_immutable.registerSpace);

                        std::string visibility;
                        Core::JsonExtract<std::string>(immutable, "Visibility", visibility);
                        _sampler.m_immutable.visibility = Sampler::SamplerVisibilityFromString(visibility);
                    }

                    m_samplers.push_back(_sampler);
                }

                nlohmann::json parameters = json["Parameters"];
                for (uint32_t i = 0; i < m_parameterCount; i++)
                {
                    nlohmann::json parameter = parameters[i];

                    std::string type;
                    
                    Core::JsonExtract<std::string>(parameter, "Type", type);

                    Parameter p;
                    p.type = ParameterTypeFromString(type);
                    switch (p.type)
                    {
                        //Initialize parameter as table
                    case RootLayout::Parameter::Type::TABLE:
                    {
                        DescriptorTable table;
                        Core::JsonExtract<uint32_t>(parameter, "RangeCount", table.rangeCount);
                        nlohmann::json ranges = parameter["Ranges"];
                        for (size_t j = 0; j < ranges.size(); j++)
                        {
                            //Load table ranges
                            std::string rangeType;
                            Core::JsonExtract<std::string>(ranges[j], "Type", rangeType);

                            Range range;
                            range.type = RangeTypeFromString(rangeType);
                            Core::JsonExtract<uint32_t>(ranges[j], "DescriptorCount", range.numDescriptors);
                            Core::JsonExtract<uint32_t>(ranges[j], "BaseRegister", range.baseRegister);
                            Core::JsonExtract<uint32_t>(ranges[j], "RegisterSpace", range.registerSpace);

                            table.ranges.push_back(range);
                        }

                        p.data.table = table;
                    } break;

                                    //Initialize parameter as a Constant
                    case RootLayout::Parameter::Type::CONSTANTS:
                    {
                        Constant constant;
                        
                        Core::JsonExtract<uint32_t>(parameter, "ShaderRegister", constant.shaderRegister);
                        Core::JsonExtract<uint32_t>(parameter, "RegisterSpace", constant.registerSpace);

                        std::string typeName;
                        Core::JsonExtract<std::string>(parameter, "DataType", typeName);

                        constant.type = ShaderVariable::TypeFromString(typeName);
                        
                        Core::JsonExtract<uint32_t>(parameter, "ValueCount", constant.valueCount);

                        p.data.constant = constant;
                    } break;

                    default:
                        break;
                    }

                    std::string visibility;
                    Core::JsonExtract<std::string>(parameter, "Visibility", visibility);
                    p.visibility = ParameterVisibilityFromString(visibility);

                    m_parameters.push_back(p);
                }
            }
            else
            {
                HT_DEBUG_PRINTF("RootLayout::Initialize(): Error reading json file at %s", fileName);
                return false;
            }
                
            return true;
        }
        
        uint32_t RootLayout::GetParameterCount() const
        {
            return m_parameterCount;
        }
        
        Core::BitField<RootLayout::Flags> RootLayout::GetDescriptorFlags() const
        {
            return m_flags;
        }

        const std::vector<RootLayout::Parameter>& RootLayout::GetParameters() const
        {
            return m_parameters;
        }

        const std::vector<Sampler>& RootLayout::GetSamplers() const
        {
            return m_samplers;
        }

        RootLayout::Parameter::Type RootLayout::ParameterTypeFromString(std::string s)
        {
            RootLayout::Parameter::Type type;

            if (s == "TABLE")
                type = RootLayout::Parameter::Type::TABLE;
            else if (s == "CONSTANTS")
                type = RootLayout::Parameter::Type::CONSTANTS;
            else if (s == "CONSTANT_BUFFER")
                type = RootLayout::Parameter::Type::CONSTANT_BUFFER;
            else if (s == "SHADER_RESOURCE")
                type = RootLayout::Parameter::Type::SHADER_RESOURCE;
            else if (s == "UNORDERED_ACCESS")
                type = RootLayout::Parameter::Type::UNORDERED_ACCESS;
            else
                type = RootLayout::Parameter::Type::UNKNOWN;

            return type;
        }

        RootLayout::Range::Type RootLayout::RangeTypeFromString(std::string s)
        {
            RootLayout::Range::Type type;

            if (s == "CONSTANT_BUFFER")
                type = RootLayout::Range::Type::CONSTANT_BUFFER;
            else if (s == "SHADER_RESOURCE")
                type = RootLayout::Range::Type::SHADER_RESOURCE;
            else if (s == "UNORDERED_ACCESS")
                type = RootLayout::Range::Type::UNORDERED_ACCESS;
            else if (s == "SAMPLER")
                type = RootLayout::Range::Type::SAMPLER;

            return type;
        }

        RootLayout::ShaderVisibility RootLayout::ParameterVisibilityFromString(std::string s)
        {
            RootLayout::ShaderVisibility visibility;

            if (s == "ALL")
                visibility = RootLayout::ShaderVisibility::ALL;
            else if (s == "VERTEX")
                visibility = RootLayout::ShaderVisibility::VERTEX;
            else if (s == "TESS_CONSTROL")
                visibility = RootLayout::ShaderVisibility::TESS_CONTROL;
            else if (s == "TESS_EVAL")
                visibility = RootLayout::ShaderVisibility::TESS_EVAL;
            else if (s == "GEOMETRY")
                visibility = RootLayout::ShaderVisibility::GEOMETRY;
            else if (s == "FRAGMENT")
                visibility = RootLayout::ShaderVisibility::FRAGMENT;
            else
                visibility = RootLayout::ShaderVisibility::UNKNOWN;

            return visibility;
        }

        RootLayout::Flags RootLayout::FlagFromString(std::string s)
        {
            Flags f = LAYOUT_FLAG_NONE;

            if (s == "LAYOUT_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT")
                f = LAYOUT_ALLOW_INPUT_ASSEMLBER_INPUT_LAYOUT;
            else if (s == "LAYOUT_DENY_VERTEX_SHADER_ROOT_ACCESS")
                f = LAYOUT_DENY_VERTEX_SHADER_ROOT_ACCESS;
            else if (s == "LAYOUT_DENY_TESS_CONTROL_SHADER_ROOT_ACCESS")
                f = LAYOUT_DENY_TESS_CONTROL_SHADER_ROOT_ACCESS;
            else if (s == "LAYOUT_DENY_TESS_EVAL_SHADER_ROOT_ACCESS")
                f = LAYOUT_DENY_TESS_EVAL_SHADER_ROOT_ACCESS;
            else if (s == "LAYOUT_DENY_GEOMETRY_SHADER_ROOT_ACCESS")
                f = LAYOUT_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
            else if (s == "LAYOUT_DENY_FRAGMENT_SHADER_ROOT_ACCESS")
                f = LAYOUT_DENY_FRAGMENT_SHADER_ROOT_ACCESS;
            else if (s == "LAYOUT_ALLOW_STREAM_OUTPUT")
                f = LAYOUT_ALLOW_STREAM_OUTPUT;
            else
                f = LAYOUT_FLAG_NONE;

            return f;
        }

        
    }
}
