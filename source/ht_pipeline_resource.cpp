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
#include <ht_debug.h>

namespace Hatchit {

    namespace Resource {

        //Still need this for HT_DEBUG_PRINTF ...
        using namespace Core;

        Pipeline::Pipeline(Core::Guid ID) : FileResource<Pipeline>(std::move(ID)) {}

        bool Pipeline::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::Pipelines) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                //Extract render pass path
                Core::JsonExtract<std::string>(json, "RenderPass", m_renderPassPath);

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
                Core::JsonExtract<std::string>(spvShaders, "Vertex", vertexPath);
                Core::JsonExtract<std::string>(spvShaders, "Fragment", fragmentPath);
                Core::JsonExtract<std::string>(spvShaders, "Geometry", geometryPath);
                Core::JsonExtract<std::string>(spvShaders, "Tess_Control", tessControlPath);
                Core::JsonExtract<std::string>(spvShaders, "Tess_Eval", tessEvalPath);
                Core::JsonExtract<std::string>(spvShaders, "Compute", computePath);

                ShaderHandle vertexHandle = Shader::GetHandleFromFileName(vertexPath);
                ShaderHandle fragmentHandle = Shader::GetHandleFromFileName(fragmentPath);
                ShaderHandle geometryHandle = Shader::GetHandleFromFileName(geometryPath);
                ShaderHandle tessControlHandle = Shader::GetHandleFromFileName(tessControlPath);
                ShaderHandle tessEvalHandle = Shader::GetHandleFromFileName(tessEvalPath);
                ShaderHandle computeHandle = Shader::GetHandleFromFileName(computePath);

                //Load SPV Shaders by handle
                if (vertexHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::VERTEX] = vertexPath;
                    m_spvShaderHandles[ShaderSlot::VERTEX] = vertexHandle;
                }
                if (fragmentHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::FRAGMENT] = fragmentPath;
                    m_spvShaderHandles[ShaderSlot::FRAGMENT] = fragmentHandle;
                }
                if (geometryHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::GEOMETRY] = geometryPath;
                    m_spvShaderHandles[ShaderSlot::GEOMETRY] = geometryHandle;
                }
                if (tessControlHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::TESS_CONTROL] = tessControlPath;
                    m_spvShaderHandles[ShaderSlot::TESS_CONTROL] = tessControlHandle;
                }
                if (tessEvalHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::TESS_EVAL] = tessEvalPath;
                    m_spvShaderHandles[ShaderSlot::TESS_EVAL] = tessEvalHandle;
                }
                if (computeHandle.IsValid())
                {
                    m_spvShaderPaths[ShaderSlot::COMPUTE] = computePath;
                    m_spvShaderHandles[ShaderSlot::COMPUTE] = computeHandle;
                }

                //Extract CSO shader path
                //Reuse existing string objects
                Core::JsonExtract<std::string>(csoShaders, "Vertex", vertexPath);
                Core::JsonExtract<std::string>(csoShaders, "Fragment", fragmentPath);
                Core::JsonExtract<std::string>(csoShaders, "Geometry", geometryPath);
                Core::JsonExtract<std::string>(csoShaders, "Tess_Control", tessControlPath);
                Core::JsonExtract<std::string>(csoShaders, "Tess_Eval", tessEvalPath);
                Core::JsonExtract<std::string>(csoShaders, "Compute", computePath);

                vertexHandle = Shader::GetHandleFromFileName(vertexPath);
                fragmentHandle = Shader::GetHandleFromFileName(fragmentPath);
                geometryHandle = Shader::GetHandleFromFileName(geometryPath);
                tessControlHandle = Shader::GetHandleFromFileName(tessControlPath);
                tessEvalHandle = Shader::GetHandleFromFileName(tessEvalPath);
                computeHandle = Shader::GetHandleFromFileName(computePath);

                if (vertexHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::VERTEX] = vertexPath;
                    m_csoShaderHandles[ShaderSlot::VERTEX] = vertexHandle;
                }
                if (fragmentHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::FRAGMENT] = fragmentPath;
                    m_csoShaderHandles[ShaderSlot::FRAGMENT] = fragmentHandle;
                }
                if (geometryHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::GEOMETRY] = geometryPath;
                    m_csoShaderHandles[ShaderSlot::GEOMETRY] = geometryHandle;
                }
                if (tessControlHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::TESS_CONTROL] = tessControlPath;
                    m_csoShaderHandles[ShaderSlot::TESS_CONTROL] = tessControlHandle;
                }
                if (tessEvalHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::TESS_EVAL] = tessEvalPath;
                    m_csoShaderHandles[ShaderSlot::TESS_EVAL] = tessEvalHandle;
                }
                if (computeHandle.IsValid())
                {
                    m_csoShaderPaths[ShaderSlot::COMPUTE] = computePath;
                    m_csoShaderHandles[ShaderSlot::COMPUTE] = computeHandle;
                }

                // Extract the vertex attributes
                nlohmann::json vertexLayout = json["VertexLayout"];
                for (size_t i = 0; i < vertexLayout.size(); i++)
                {
                    Attribute attribute;

                    Core::JsonExtract<std::string>(vertexLayout[i], "SemanticName", attribute.semanticName);
                    Core::JsonExtract<uint32_t>(vertexLayout[i], "SemanticIndex", attribute.semanticIndex);

                    std::string type;
                    Core::JsonExtract<std::string>(vertexLayout[i], "Type", type);
                    attribute.type = ShaderVariable::TypeFromString(type);

                    Core::JsonExtract<uint32_t>(vertexLayout[i], "Slot", attribute.slot);

                    m_vertexLayout.push_back(attribute);
                }

                // Extract the instance attributes
                nlohmann::json instanceLayout = json["InstanceLayout"];
                for (size_t i = 0; i < instanceLayout.size(); i++)
                {
                    Attribute attribute;

                    Core::JsonExtract<std::string>(instanceLayout[i], "SemanticName", attribute.semanticName);
                    Core::JsonExtract<uint32_t>(instanceLayout[i], "SemanticIndex", attribute.semanticIndex);

                    std::string type;
                    Core::JsonExtract<std::string>(instanceLayout[i], "Type", type);
                    attribute.type = ShaderVariable::TypeFromString(type);

                    Core::JsonExtract<uint32_t>(instanceLayout[i], "Slot", attribute.slot);

                    m_instanceLayout.push_back(attribute);
                }

                // Extract Depth Stencil state
                nlohmann::json json_depthState = json["DepthStencilState"];
                Core::JsonExtract<bool>(json_depthState, "TestDepth", m_depthStencilState.testDepth);
                Core::JsonExtract<bool>(json_depthState, "WriteDepth", m_depthStencilState.writeDepth);

                // Extract Rasterizer state
                nlohmann::json json_rasterState = json["RasterState"];
                std::string polygonMode;
                std::string cullMode;

                Core::JsonExtract<std::string>(json_rasterState, "PolygonMode", polygonMode);
                Core::JsonExtract<std::string>(json_rasterState, "CullMode", cullMode);
                Core::JsonExtract<bool>(json_rasterState, "FrontCounterClockwise", m_rasterizationState.frontCounterClockwise);
                Core::JsonExtract<bool>(json_rasterState, "DepthClampEnable", m_rasterizationState.depthClampEnable);
                Core::JsonExtract<bool>(json_rasterState, "DiscardEnable", m_rasterizationState.discardEnable);
                Core::JsonExtract<float>(json_rasterState, "LineWidth", m_rasterizationState.lineWidth);


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

                Core::JsonExtract<int64_t>(json_multisampleState, "SampleCount", sampleCount);
                Core::JsonExtract<float>(json_multisampleState, "MinSamples", m_multisampleState.minSamples);
                Core::JsonExtract<bool>(json_multisampleState, "PerSampleShading", m_multisampleState.perSampleShading);

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
                //std::string name;
                std::string type;

                for (size_t i = 0; i < shaderVariables.size(); i++)
                {
                    //they have names but we don't really care what they are, we just create them in the order they appear in the file
                    //Core::JsonExtract<std::string>(shaderVariables[i], "Name", name);
                    Core::JsonExtract<std::string>(shaderVariables[i], "Type", type);

                    if (type == "INT" || type == "Int")
                    {
                        uint32_t value;
                        Core::JsonExtract<uint32_t>(shaderVariables[i], "Value", value);
                        m_shaderVariables.push_back(new IntVariable(value));
                    }
                    else if (type == "FLOAT" || type == "Float")
                    {
                        float value;
                        Core::JsonExtract<float>(shaderVariables[i], "Value", value);
                        m_shaderVariables.push_back(new FloatVariable(value));
                    }
                    else if (type == "DOUBLE" || type == "Double")
                    {
                        double value;
                        Core::JsonExtract<double>(shaderVariables[i], "Value", value);
                        m_shaderVariables.push_back(new DoubleVariable(value));
                    }
                    else if (type == "FLOAT2" || type == "Float2")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector2 vec = Math::Vector2(jsonVec[0], jsonVec[1]);
                        m_shaderVariables.push_back(new Float2Variable(vec));
                    }
                    else if (type == "FLOAT3" || type == "Float3")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector3 vec = Math::Vector3(jsonVec[0], jsonVec[1], jsonVec[2]);
                        m_shaderVariables.push_back(new Float3Variable(vec));
                    }
                    else if (type == "FLOAT4" || type == "Float4")
                    {
                        nlohmann::json jsonVec = shaderVariables[i]["Value"];
                        Math::Vector4 vec = Math::Vector4(jsonVec[0], jsonVec[1], jsonVec[2], jsonVec[3]);
                        m_shaderVariables.push_back(new Float4Variable(vec));
                    }
                    else if (type == "MATRIX4" || type == "Matrix4")
                    {
                        nlohmann::json jsonMat = shaderVariables[i]["Value"];
                        Math::Matrix4 mat = Math::Matrix4(jsonMat[0], jsonMat[1], jsonMat[2], jsonMat[3],
                            jsonMat[4], jsonMat[5], jsonMat[6], jsonMat[7],
                            jsonMat[8], jsonMat[9], jsonMat[10], jsonMat[11],
                            jsonMat[12], jsonMat[13], jsonMat[14], jsonMat[15]);
                        m_shaderVariables.push_back(new Matrix4Variable(mat));
                    }
                }

                jsonStream.close();
                return true;
            }
            else
            {
                HT_DEBUG_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::Pipelines) + fileName);
                return false;
            }
        }

        const std::string& Pipeline::GetRenderPassPath() const 
        {
            return m_renderPassPath;
        }

        const Pipeline::DepthStencilState& Pipeline::GetDepthStencilState() const
        {
            return m_depthStencilState;
        }

        const Pipeline::RasterizerState& Pipeline::GetRasterizationState() const
        { 
            return m_rasterizationState;
        }

        const Pipeline::MultisampleState& Pipeline::GetMultisampleState() const 
        { 
            return m_multisampleState; 
        }

        const std::vector<Pipeline::Attribute>& Pipeline::GetVertexLayout() const
        {
            return m_vertexLayout;
        }

        const std::vector<Pipeline::Attribute>& Pipeline::GetInstanceLayout() const
        {
            return m_instanceLayout;
        }

        const std::vector<ShaderVariable*>& Pipeline::GetShaderVariables() const 
        { 
            return m_shaderVariables;
        }

        const std::map<Pipeline::ShaderSlot, std::string>& Pipeline::GetSPVShaderPaths() const
        { 
            return m_spvShaderPaths; 
        }
        const std::map<Pipeline::ShaderSlot, std::string>& Pipeline::GetCSOShaderPaths() const
        {
            return m_csoShaderPaths;
        }

        const std::map<Pipeline::ShaderSlot, ShaderHandle>& Pipeline::GetSPVShaderHandles() const
        { 
            return m_spvShaderHandles;
        }
        const std::map<Pipeline::ShaderSlot, ShaderHandle>& Pipeline::GetCSOShaderHandles() const
        {
            return m_csoShaderHandles; 
        }

    }

}
