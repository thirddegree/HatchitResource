#pragma once

#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Material : public Resource<Material>
        {
        public:
            Material(std::string name);
            virtual ~Material() = default;


            virtual bool VInitFromFile(const std::string& file) override;

        private:
            std::string m_pipeline;
            std::string m_renderPass;
            std::vector<std::string> m_shaderVariables;
            std::vector<std::string> m_textures;
        };

        using MaterialHandle = Material::Handle;
    }
}