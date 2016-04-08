/**
**    Hatchit Engine
<<<<<<< Updated upstream
**    Copyright(c) 2015 Third-Degree
=======
**    Copyright(c) 2015-2016 ThirdDegree
>>>>>>> Stashed changes
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
            Material(std::string ID, const std::string& fileName);
            virtual ~Material() = default;

            const std::string& GetPipelinePath() const;
            const std::string& GetRenderPassPath() const;
            std::map<std::string, ShaderVariable*> GetShaderVariables() const;
            std::vector<std::string> GetTexturePaths() const;

        private:
            std::string m_pipelinePath;
            std::string m_renderPassPath;
            std::map<std::string, ShaderVariable*> m_shaderVariables;
            std::vector<std::string> m_texturePaths;
        };

        using MaterialHandle = Core::Handle<const Material>;
    }
}