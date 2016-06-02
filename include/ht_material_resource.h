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

#pragma once

#include <ht_resource.h>
#include <ht_shadervariable.h>
#include <ht_pipeline_resource.h>
#include <ht_renderpass_resource.h>
#include <ht_texture_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Material : public FileResource<Material>
        {
        public:
            struct TexturePath
            {
                std::string path;
                uint32_t set;
                uint32_t binding;
            };

            struct ShaderVariableBinding
            {
                std::vector<ShaderVariable*> shaderVariables;
                uint32_t set;
                uint32_t binding;
            };
            
            Material(Core::Guid ID);
            virtual ~Material() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

            const std::string& GetPipelinePath() const;
            const std::vector<std::string>& GetRenderPassPaths() const;
            std::vector<ShaderVariableBinding> GetShaderVariables() const;
            std::vector<TexturePath> GetTexturePaths() const;

        private:
            std::string m_pipelinePath;
            std::vector<std::string> m_renderPassPaths;
            std::vector<ShaderVariableBinding> m_shaderVariables;
            std::vector<TexturePath> m_texturePaths;
        };

        using MaterialHandle = Core::Handle<const Material>;
    }
}