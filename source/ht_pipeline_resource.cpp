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

        Pipeline::Pipeline(std::string name) : FileResource<Pipeline>(std::move(name)) {}

        bool Pipeline::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::Pipelines) + filename);

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

                ShaderHandle vertexHandle       = Shader::GetHandle(vertexPath);
                ShaderHandle fragmentHandle     = Shader::GetHandle(fragmentPath);
                ShaderHandle geometryHandle     = Shader::GetHandle(geometryPath);
                ShaderHandle tessControlHandle  = Shader::GetHandle(tessControlPath);
                ShaderHandle tessEvalHandle     = Shader::GetHandle(tessEvalPath);
                ShaderHandle computeHandle      = Shader::GetHandle(computePath);

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

                vertexHandle        = Shader::GetHandle(vertexPath);
                fragmentHandle      = Shader::GetHandle(fragmentPath);
                geometryHandle      = Shader::GetHandle(geometryPath);
                tessControlHandle   = Shader::GetHandle(tessControlPath);
                tessEvalHandle      = Shader::GetHandle(tessEvalPath);
                computeHandle       = Shader::GetHandle(computePath);

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

                JsonExtractString(json_rasterState, "PolygonMode", polygonMode);
                JsonExtractString(json_rasterState, "CullMode", cullMode);
                JsonExtractBool(json_rasterState, "FrontCounterClockwise", m_rasterizationState.frontCounterClockwise);
                JsonExtractBool(json_rasterState, "DepthClampEnable", m_rasterizationState.depthClampEnable);
                JsonExtractBool(json_rasterState, "DiscardEnable", m_rasterizationState.discardEnable);
                JsonExtractFloat(json_rasterState, "LineWidth", m_rasterizationState.lineWidth);

                if (polygonMode == "LINE" || polygonMode == "Line")
                    m_rasterizationState.polygonMode = PolygonMode::LINE;
                else
                    m_rasterizationState.polygonMode = PolygonMode::SOLID;

                if (cullMode == "FRONT" || cullMode == "Front")
                    m_rasterizationState.cullMode = CullMode::FRONT;
                else if (cullMode == "BACK" || cullMode == "Back")
                    m_rasterizationState.cullMode = CullMode::BACK;
                else
                    m_rasterizationState.cullMode = CullMode::NONE;

                // Extract Multisampler state
                nlohmann::json json_multisampleState = json["MultisampleState"];
                int64_t sampleCount;

                JsonExtractInt64(json_multisampleState, "SampleCount", sampleCount);
                JsonExtractFloat(json_multisampleState, "MinSamples", m_multisampleState.minSamples);
                JsonExtractBool(json_multisampleState, "PerSampleShading", m_multisampleState.perSampleShading);

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
                    JsonExtractString(shaderVariables[i], "Name", name);
                    JsonExtractString(shaderVariables[i], "Type", type);

                    if (type == "INT" || type == "Int")
                    {
                        uint32_t value;
                        JsonExtractUint32(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new IntVariable(value);
                    }
                    else if (type == "FLOAT" || type == "Float")
                    {
                        float value;
                        JsonExtractFloat(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new FloatVariable(value);
                    }
                    else if (type == "DOUBLE" || type == "Double")
                    {
                        double value;
                        JsonExtractDouble(shaderVariables[i], "Value", value);
                        m_shaderVariables[name] = new DoubleVariable(value);
                    }
                    else if (type == "FLOAT2" || type == "Float2")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector2 vec = Math::Vector2(jsonVec[0], jsonVec[1]);
                        m_shaderVariables[name] = new Float2Variable(vec);
                    }
                    else if (type == "FLOAT3" || type == "Float3")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector3 vec = Math::Vector3(jsonVec[0], jsonVec[1], jsonVec[2]);
                        m_shaderVariables[name] = new Float3Variable(vec);
                    }
                    else if (type == "FLOAT4" || type == "Float4")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector4 vec = Math::Vector4(jsonVec[0], jsonVec[1], jsonVec[2], jsonVec[3]);
                        m_shaderVariables[name] = new Float4Variable(vec);
                    }
                    else if (type == "MATRIX4" || type == "Matrix4")
                    {
                        nlohmann::json jsonMat = shaderVariables[i]["Value"];
                        Math::Matrix4 mat = Math::Matrix4(jsonMat[0], jsonMat[1], jsonMat[2], jsonMat[3],
                            jsonMat[4], jsonMat[5], jsonMat[6], jsonMat[7],
                            jsonMat[8], jsonMat[9], jsonMat[10], jsonMat[11],
                            jsonMat[12], jsonMat[13], jsonMat[14], jsonMat[15]);
                        m_shaderVariables[name] = new Matrix4Variable(mat);
                    }
                }

                jsonStream.close();
                return true;
            }

            DebugPrintF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::Pipelines) + filename);
            return false;
        }

        const Pipeline::RasterizerState& Pipeline::GetRasterizationState() const { return m_rasterizationState; }
        const Pipeline::MultisampleState& Pipeline::GetMultisampleState() const { return m_multisampleState; }

        const std::map<std::string, ShaderVariable*>& Pipeline::GetShaderVariables() const { return m_shaderVariables; }

        const std::map<Pipeline::ShaderSlot, ShaderHandle>& Pipeline::GetSPVShaderPaths() const { return m_spvShaderHandles; }
        const std::map<Pipeline::ShaderSlot, ShaderHandle>& Pipeline::GetCSOShaderPaths() const { return m_csoShaderHandles; }
    }

}