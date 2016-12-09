/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

#include <ht_platform.h>
#include <ht_fileresource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API RenderPass : public FileResource<RenderPass>
        {
        public:
            RenderPass(uint64_t id);

            ~RenderPass();

            bool Initialize(const std::string& path);

            struct Input
            {
                std::string path;
                uint32_t    set;
                uint32_t    binding;
            };

            const std::string&                      GetLayout() const;
            const std::vector<RenderPass::Input>&   GetInputs() const;
            const std::vector<std::string>&         GetOutputs() const;
        private:
            std::string                     m_layout;
            std::vector<RenderPass::Input>  m_inputs;
            std::vector<std::string>        m_outputs;
        };
        using RenderPassHandle = Handle<const RenderPass>;
    }
}