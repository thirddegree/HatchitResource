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

                //Extract shaders
                nlohmann::json shaderPaths = json["Shaders"];
                nlohmann::json spvShaders = shaderPaths["spv"];
                nlohmann::json csoShaders = shaderPaths["cso"];

                std::string vertexPath;
                std::string fragmentPath;
                std::string geometryPath;
                std::string tessControlPath;
                std::string tessEvalPath;
                std::string computePath;

                //Extract SPV shader paths
                JsonExtractString(spvShaders, "Vertex", vertexPath);
                JsonExtractString(spvShaders, "Fragment", fragmentPath);
                JsonExtractString(spvShaders, "Geometry", geometryPath);
                JsonExtractString(spvShaders, "Tess_Control", tessControlPath);
                JsonExtractString(spvShaders, "Tess_Eval", tessEvalPath);
                JsonExtractString(spvShaders, "Compute", computePath);

                ShaderHandle vertexHandle       = Shader::GetResourceHandle(vertexPath);
                ShaderHandle fragmentHandle     = Shader::GetResourceHandle(fragmentPath);
                ShaderHandle geometryHandle     = Shader::GetResourceHandle(geometryPath);
                ShaderHandle tessControlHandle  = Shader::GetResourceHandle(tessControlPath);
                ShaderHandle tessEvalHandle     = Shader::GetResourceHandle(tessEvalPath);
                ShaderHandle computeHandle      = Shader::GetResourceHandle(computePath);

                //Load SPV Shaders by handle
                if(vertexHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::VERTEX]          = vertexHandle;
                if (fragmentHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::FRAGMENT]        = fragmentHandle;
                if (geometryHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::GEOMETRY]        = geometryHandle;
                if (tessControlHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::TESS_CONTROL]    = tessControlHandle;
                if (tessEvalHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::TESS_EVAL]       = tessEvalHandle;
                if (computeHandle.IsValid())
                    m_spvShaderHandles[ShaderSlot::COMPUTE]         = computeHandle;

                //Extract CSO shader path
                //Reuse existing string objects
                JsonExtractString(csoShaders, "Vertex",         vertexPath);
                JsonExtractString(csoShaders, "Fragment",       fragmentPath);
                JsonExtractString(csoShaders, "Geometry",       geometryPath);
                JsonExtractString(csoShaders, "Tess_Control",   tessControlPath);
                JsonExtractString(csoShaders, "Tess_Eval",      tessEvalPath);
                JsonExtractString(csoShaders, "Compute",        computePath);

                vertexHandle        = Shader::GetResourceHandle(vertexPath);
                fragmentHandle      = Shader::GetResourceHandle(fragmentPath);
                geometryHandle      = Shader::GetResourceHandle(geometryPath);
                tessControlHandle   = Shader::GetResourceHandle(tessControlPath);
                tessEvalHandle      = Shader::GetResourceHandle(tessEvalPath);
                computeHandle       = Shader::GetResourceHandle(computePath);

                if (vertexHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::VERTEX] = vertexHandle;
                if (fragmentHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::FRAGMENT] = fragmentHandle;
                if (geometryHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::GEOMETRY] = geometryHandle;
                if (tessControlHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::TESS_CONTROL] = tessControlHandle;
                if (tessEvalHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::TESS_EVAL] = tessEvalHandle;
                if (computeHandle.IsValid())
                    m_csoShaderHandles[ShaderSlot::COMPUTE] = computeHandle;

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

        std::map<Pipeline::ShaderSlot, ShaderHandle> Pipeline::GetSPVShaderPaths() { return m_spvShaderHandles; }
        std::map<Pipeline::ShaderSlot, ShaderHandle> Pipeline::GetCSOShaderPaths() { return m_csoShaderHandles; }
    }

}