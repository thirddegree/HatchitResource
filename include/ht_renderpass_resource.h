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

namespace Hatchit
{
    namespace Resource
    {
        class HT_API RenderPass : public Resource<RenderPass>
        {
        public:
            RenderPass(std::string name);
            virtual ~RenderPass() = default;

            virtual bool VInitFromFile(const std::string& fileName) override;
        private:
            std::vector<std::string> m_inputPaths;
            std::vector<std::string> m_outputPaths;
        };

        using RenderPassHandle = RenderPass::Handle;
    }
}