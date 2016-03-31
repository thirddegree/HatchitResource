/**
**    Hatchit Engine
**    Copyright(c) 2015 ThirdDegree
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

#include <ht_pipeline_resource.h>

namespace Hatchit {

    namespace Resource {
    
        //Required for JsonExtractString etc.
        using namespace Core;

        Pipeline::Pipeline(std::string name) : Resource(std::move(name)) {}

        bool Pipeline::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::os_exec_dir() + filename);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                //Extract shader paths
                nlohmann::json shaderPaths = json["Shaders"];
                nlohmann::json spvShaders = shaderPaths["spv"];
                nlohmann::json csoShaders = shaderPaths["cso"];

                JsonExtractString(spvShaders, "Vertex",          m_spvShaderPaths[ShaderSlot::VERTEX]);
                JsonExtractString(spvShaders, "Fragment",        m_spvShaderPaths[ShaderSlot::FRAGMENT]);
                JsonExtractString(spvShaders, "Geometry",        m_spvShaderPaths[ShaderSlot::GEOMETRY]);
                JsonExtractString(spvShaders, "Tess_Control",    m_spvShaderPaths[ShaderSlot::TESS_CONTROL]);
                JsonExtractString(spvShaders, "Tess_Eval",       m_spvShaderPaths[ShaderSlot::TESS_EVAL]);
                JsonExtractString(spvShaders, "Compute",         m_spvShaderPaths[ShaderSlot::COMPUTE]);

                JsonExtractString(csoShaders, "Vertex",          m_csoShaderPaths[ShaderSlot::VERTEX]);
                JsonExtractString(csoShaders, "Fragment",        m_csoShaderPaths[ShaderSlot::FRAGMENT]);
                JsonExtractString(csoShaders, "Geometry",        m_csoShaderPaths[ShaderSlot::GEOMETRY]);
                JsonExtractString(csoShaders, "Tess_Control",    m_csoShaderPaths[ShaderSlot::TESS_CONTROL]);
                JsonExtractString(csoShaders, "Tess_Eval",       m_csoShaderPaths[ShaderSlot::TESS_EVAL]);
                JsonExtractString(csoShaders, "Compute",         m_csoShaderPaths[ShaderSlot::COMPUTE]);


                // Extract Rasterizer state
                nlohmann::json json_rasterState = json["RasterState"];
                std::string polygonMode;
                std::string cullMode;
                double lineWidth;

                JsonExtractString(json_rasterState, "PolygonMode", polygonMode);
                JsonExtractString(json_rasterState, "CullMode", cullMode);
                JsonExtractBool(json_rasterState, "FrontCounterClockwise", m_rasterizationState.frontCounterClockwise);
                JsonExtractBool(json_rasterState, "DepthClampEnable", m_rasterizationState.depthClampEnable);
                JsonExtractBool(json_rasterState, "DiscardEnable", m_rasterizationState.discardEnable);
                JsonExtractDouble(json_rasterState, "LineWidth", lineWidth);

                m_rasterizationState.lineWidth = static_cast<float>(lineWidth);

                if (polygonMode == "LINE")
                    m_rasterizationState.polygonMode = PolygonMode::LINE;
                else
                    m_rasterizationState.polygonMode = PolygonMode::SOLID;

                if (cullMode == "FRONT")
                    m_rasterizationState.cullMode = CullMode::FRONT;
                else if (cullMode == "BACK")
                    m_rasterizationState.cullMode = CullMode::BACK;
                else
                    m_rasterizationState.cullMode = CullMode::NONE;

                // Extract Multisampler state
                nlohmann::json json_multisampleState = json["MultisampleState"];
                int64_t sampleCount;
                double minSamples;

                JsonExtractInt64(json_multisampleState, "SampleCount", sampleCount);
                JsonExtractDouble(json_multisampleState, "MinSamples", minSamples);
                JsonExtractBool(json_multisampleState, "PerSampleShading", m_multisampleState.perSampleShading);

                m_multisampleState.minSamples = static_cast<float>(minSamples);

                switch (sampleCount)
                {
                case 1:
                    m_multisampleState.samples = SampleCount::SAMPLE_1_BIT;
                    break;
                case 2:
                    m_multisampleState.samples = SampleCount::SAMPLE_2_BIT;
                    break;
                case 4:
                    m_multisampleState.samples = SampleCount::SAMPLE_4_BIT;
                    break;
                case 8:
                    m_multisampleState.samples = SampleCount::SAMPLE_8_BIT;
                    break;
                case 16:
                    m_multisampleState.samples = SampleCount::SAMPLE_16_BIT;
                    break;
                case 32:
                    m_multisampleState.samples = SampleCount::SAMPLE_32_BIT;
                    break;
                case 64:
                    m_multisampleState.samples = SampleCount::SAMPLE_64_BIT;
                    break;
                }

                // Extract ShaderVariables
                nlohmann::json shaderVariables = json["ShaderVariables"];
                std::string name;
                std::string type;

                for (unsigned i = 0; i < shaderVariables.size(); i++)
                {
                    Core::JsonExtractString(shaderVariables[i], "Name", name);
                    JsonExtractString(shaderVariables[i], "Type", type);

                    if (type == "INT")
                    {
                        uint64_t value;
                        JsonExtractUint64(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new IntVariable(static_cast<uint32_t>(value));
                    }
                    else if (type == "FLOAT")
                    {
                        double value;
                        JsonExtractDouble(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new FloatVariable(static_cast<float>(value));
                    }
                    else if (type == "DOUBLE")
                    {
                        double value;
                        JsonExtractDouble(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new DoubleVariable(value);
                    }
                    else if (type == "FLOAT2")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector2 vec = Math::Vector2(jsonVec[0], jsonVec[1]);
                        m_shaderVariables[name] = new Float2Variable(vec);
                    }
                    else if (type == "FLOAT3")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector3 vec = Math::Vector3(jsonVec[0], jsonVec[1], jsonVec[2]);
                        m_shaderVariables[name] = new Float3Variable(vec);
                    }
                    else if (type == "FLOAT4")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector4 vec = Math::Vector4(jsonVec[0], jsonVec[1], jsonVec[2], jsonVec[3]);
                        m_shaderVariables[name] = new Float4Variable(vec);
                    }
                    else if (type == "MATRIX4")
                    {
                        nlohmann::json jsonMat = shaderVariables[i]["Value"];
                        Math::Matrix4 mat = Math::Matrix4(jsonMat[0], jsonMat[1], jsonMat[2], jsonMat[3],
                            jsonMat[4], jsonMat[5], jsonMat[6], jsonMat[7],
                            jsonMat[8], jsonMat[9], jsonMat[10], jsonMat[11],
                            jsonMat[12], jsonMat[13], jsonMat[14], jsonMat[15]);
                        m_shaderVariables[name] = new Matrix4Variable(mat);
                    }
                }

                return true;
            }

            DebugPrintF("ERROR: Could not generate stream to JSON file -> %s", filename);
            return true;
        }

        Pipeline::RasterizerState Pipeline::GetRasterizationState() { return m_rasterizationState; }
        Pipeline::MultisampleState Pipeline::GetMultisampleState() { return m_multisampleState; }

        std::map<std::string, ShaderVariable*> Pipeline::GetShaderVariables() { return m_shaderVariables; }

        std::map<Pipeline::ShaderSlot, std::string> Pipeline::GetSPVShaderPaths() { return m_spvShaderPaths; }
        std::map<Pipeline::ShaderSlot, std::string> Pipeline::GetCSOShaderPaths() { return m_csoShaderPaths; }
    }

}