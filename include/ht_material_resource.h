#pragma once

#include <ht_resource.h>
#include <ht_shadervariable.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Material : public Resource<Material>
        {
        public:
            Material(std::string filename);
            virtual ~Material() = default;

            virtual bool VInitFromFile(const std::string& filename) override;

        private:
            std::string m_pipeline;
            std::string m_renderPass;
            std::map<std::string, ShaderVariable*> m_shaderVariables;
            std::vector<std::string> m_textures;
        };

        using MaterialHandle = Material::Handle;
    }
}