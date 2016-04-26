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
        class HT_API RenderPass : public FileResource<RenderPass>
        {
        public:
            struct InputTarget 
            {
                std::string path;
                uint32_t set;
                uint32_t binding;
            };

            RenderPass(Core::Guid ID);
            virtual ~RenderPass() = default;

            //Required function for all RefCounted classes
            bool Initialize(const std::string& fileName);

            std::vector<InputTarget> GetInputTargets() const;
            std::vector<std::string> GetOutputPaths() const;

        private:
            std::vector<InputTarget> m_inputTargets;
            std::vector<std::string> m_outputPaths;
        };

        using RenderPassHandle = Core::Handle<const RenderPass>;
    }
}