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

#include <ht_material_resource.h>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Resource
    {
        //Still needed for HT_DEBUG_PRINTF
        using namespace Core;

        Material::Material(Core::Guid ID) : FileResource<Material>(std::move(ID)) {}

        bool Material::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::Materials) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                Core::JsonExtract<std::string>(json, "Pipeline", m_pipelinePath);
                
                //Extract render pass paths
                nlohmann::json renderPasses = json["RenderPasses"];

                for (uint32_t i = 0; i < renderPasses.size(); i++)
                {
                    std::string renderPassPath = renderPasses[i];
                    m_renderPassPaths.push_back(renderPassPath);
                }

                // Extract ShaderVariables
                nlohmann::json shaderVariables = json["ShaderVariables"];

                for (uint32_t i = 0; i < shaderVariables.size(); i++)
                {
                    nlohmann::json shaderVariable = shaderVariables[i];

                    ShaderVariableBinding shaderVariableBinding;
                    std::map<std::string, ShaderVariable*>& variableMap = shaderVariableBinding.shaderVariables;

                    nlohmann::json vars = shaderVariable["Vars"];

                    //Get set and binding
                    Core::JsonExtract<uint32_t>(shaderVariable, "Set", shaderVariableBinding.set);
                    Core::JsonExtract<uint32_t>(shaderVariable, "Binding", shaderVariableBinding.binding);

                    //Get variable map
                    for (auto var : vars)
                    {
                        std::string name;
                        std::string type;

                        Core::JsonExtract<std::string>(shaderVariable, "Name", name);
                        Core::JsonExtract<std::string>(shaderVariable, "Type", type);

                        if (type == "INT" || type == "Int")
                        {
                            uint32_t value;
                            Core::JsonExtract<uint32_t>(shaderVariables[i], "Value", value);
                            variableMap[name] = new IntVariable(value);
                        }
                        else if (type == "FLOAT" || type == "Float")
                        {
                            float value;
                            Core::JsonExtract<float>(shaderVariables[i], "Value", value);
                            variableMap[name] = new FloatVariable(value);
                        }
                        else if (type == "DOUBLE" || type == "Double")
                        {
                            double value;
                            Core::JsonExtract<double>(shaderVariables[i], "Value", value);
                            variableMap[name] = new DoubleVariable(value);
                        }
                        else if (type == "FLOAT2" || type == "Float2")
                        {
                            nlohmann::json jsonVec = shaderVariables[i]["Value"];
                            Math::Vector2 vec = Math::Vector2(jsonVec[0], jsonVec[1]);
                            variableMap[name] = new Float2Variable(vec);
                        }
                        else if (type == "FLOAT3" || type == "Float3")
                        {
                            nlohmann::json jsonVec = shaderVariables[i]["Value"];
                            Math::Vector3 vec = Math::Vector3(jsonVec[0], jsonVec[1], jsonVec[2]);
                            variableMap[name] = new Float3Variable(vec);
                        }
                        else if (type == "FLOAT4" || type == "Float4")
                        {
                            nlohmann::json jsonVec = shaderVariables[i]["Value"];
                            Math::Vector4 vec = Math::Vector4(jsonVec[0], jsonVec[1], jsonVec[2], jsonVec[3]);
                            variableMap[name] = new Float4Variable(vec);
                        }
                        else if (type == "MATRIX4" || type == "Matrix4")
                        {
                            nlohmann::json jsonMat = shaderVariables[i]["Value"];
                            Math::Matrix4 mat = Math::Matrix4(jsonMat[0], jsonMat[1], jsonMat[2], jsonMat[3],
                                jsonMat[4], jsonMat[5], jsonMat[6], jsonMat[7],
                                jsonMat[8], jsonMat[9], jsonMat[10], jsonMat[11],
                                jsonMat[12], jsonMat[13], jsonMat[14], jsonMat[15]);
                            variableMap[name] = new Matrix4Variable(mat);
                        }
                    }
                }

                //Extract texture paths
                nlohmann::json textures = json["Textures"];
                for (size_t i = 0; i < textures.size(); i++)
                {
                    nlohmann::json json_texturePath = textures[i];

                    TexturePath texturePath;
                    
                    Core::JsonExtract<std::string>(json_texturePath, "Path", texturePath.path);
                    Core::JsonExtract<uint32_t>(json_texturePath, "Set", texturePath.set);
                    Core::JsonExtract<uint32_t>(json_texturePath, "Binding", texturePath.binding);

                    m_texturePaths.push_back(texturePath);
                }

                jsonStream.close();
                return true;
            }
            else
            {
                HT_ERROR_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::Materials) + fileName);
                return false;
            }
        }

        const std::string& Material::GetPipelinePath() const { return m_pipelinePath; }
        const std::vector<std::string>& Material::GetRenderPassPaths() const { return m_renderPassPaths; }
        std::vector<Material::ShaderVariableBinding> Material::GetShaderVariables() const { return m_shaderVariables; }
        std::vector<Material::TexturePath> Material::GetTexturePaths() const { return m_texturePaths; }
    }
}
