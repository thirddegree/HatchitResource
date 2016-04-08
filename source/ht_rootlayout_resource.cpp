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
#include <algorithm>
#include <json.hpp>

namespace Hatchit
{
	namespace Resource
	{
		using namespace Core;

		RootLayout::RootLayout(std::string ID, const std::string& fileName)
			: FileResource<RootLayout>(std::move(ID))
		{
			nlohmann::json json;

			std::ifstream jsonStream(Path::Value(Path::Directory::Assets) + fileName);

			if (jsonStream.is_open())
			{
				jsonStream >> json;

				JsonExtractUint32(json, "ParameterCount", m_parameterCount);

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
                    JsonExtractString(filter, "Mag", magFilter);
                    JsonExtractString(filter, "Min", minFilter);
                    _sampler.m_filter.mag = Sampler::SamplerFilterModeFromString(magFilter);
                    _sampler.m_filter.min = Sampler::SamplerFilterModeFromString(minFilter);

                    //Parse Address
                    auto address = sampler["Address"];
                    std::string uMode;
                    std::string vMode;
                    std::string wMode;
                    JsonExtractString(address, "U", uMode);
                    JsonExtractString(address, "V", vMode);
                    JsonExtractString(address, "W", wMode);
                    _sampler.m_address.u = Sampler::SamplerAddressModeFromString(uMode);
                    _sampler.m_address.v = Sampler::SamplerAddressModeFromString(vMode);
                    _sampler.m_address.w = Sampler::SamplerAddressModeFromString(wMode);

                    
                    JsonExtractFloat(sampler, "MipLODBias", _sampler.m_mipLODBias);
                    JsonExtractFloat(sampler, "MinLOD", _sampler.m_minLOD);
                    JsonExtractFloat(sampler, "MaxLOD", _sampler.m_maxLOD);
                    JsonExtractUint32(sampler, "MaxAnisotropy", _sampler.m_maxAnisotropy);
                    
                    std::string compareOp;
                    JsonExtractString(sampler, "CompareOp", compareOp);
                    _sampler.m_compareOp = Sampler::SamplerCompareOpFromString(compareOp);

                    std::string borderColor;
                    JsonExtractString(sampler, "BorderColor", borderColor);
                    _sampler.m_borderColor = Sampler::SamplerBorderColorFromString(borderColor);

                    
                    /*Attempt to find Immutable struct*/
                    if (sampler.find("Immutable") != sampler.end())
                    {
                        //If found, we should load immutable information
                        auto immutable = sampler["Immutable"];

                        JsonExtractUint32(immutable, "Register", _sampler.m_immutable.shaderRegister);
                        JsonExtractUint32(immutable, "Space", _sampler.m_immutable.registerSpace);
                        
                        std::string visibility;
                        JsonExtractString(immutable, "Visibility", visibility);
                        _sampler.m_immutable.visibility = Sampler::SamplerVisibilityFromString(visibility);
                    }
                        
                    m_samplers.push_back(_sampler);
                }

				nlohmann::json parameters = json["Parameters"];
				for (int i = 0; i < m_parameterCount; i++)
				{
					std::string type;
					JsonExtractString(parameters[i], "Type", type);

					Parameter p;
					p.type = ParameterTypeFromString(type);
					switch (p.type)
					{
						//Initialize parameter as table
					case RootLayout::Parameter::Type::TABLE:
					{
						DescriptorTable table;
						JsonExtractUint32(parameters[i], "RangeCount", table.rangeCount);
						nlohmann::json ranges = parameters[i]["Ranges"];
						for (int j = 0; j < ranges.size(); j++)
						{
							//Load table ranges
							std::string rangeType;
							JsonExtractString(ranges[j], "Type", rangeType);

							Range range;
							range.type = RangeTypeFromString(rangeType);
							JsonExtractUint32(ranges[j], "DescriptorCount", range.numDescriptors);
							JsonExtractUint32(ranges[j], "BaseRegister", range.baseRegister);
							JsonExtractUint32(ranges[j], "RegisterSpace", range.registerSpace);

							table.ranges.push_back(range);
						}

						p.data.table = table;
					} break;

					default:
						break;
					}

					std::string visibility;
					JsonExtractString(parameters[i], "Visibility", visibility);
					p.visibility = ParameterVisibilityFromString(visibility);

					m_parameters.push_back(p);
				}
			}
				
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
			else if (s == "CONSTANT")
				type = RootLayout::Parameter::Type::CONSTANT;
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