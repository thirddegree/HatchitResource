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

#pragma once

#include <ht_resource.h>
#include <ht_shadervariable.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Material : public FileResource<Material>
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

        using MaterialHandle = Core::Handle<const Material>;
    }
}