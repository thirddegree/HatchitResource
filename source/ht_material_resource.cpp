#include <ht_material_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        using namespace Core;

        Material::Material(std::string filename) : Resource(std::move(filename)) {}

        bool Material::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::Materials) + filename);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                JsonExtractString(json, "Pipeline", m_pipeline);
                JsonExtractString(json, "RenderPass", m_renderPass);

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

            DebugPrintF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::Materials) + filename);
            return false;
        }
    }
}