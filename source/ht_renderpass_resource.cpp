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

#include <ht_renderpass_resource.h>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Resource
    {
        //Still needed for HT_DEBUG_PRINTF
        using namespace Core;

        RenderPass::RenderPass(Core::Guid ID) : FileResource<RenderPass>(std::move(ID)) {}

        bool RenderPass::Initialize(const std::string& fileName)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Core::Path::Value(Core::Path::Directory::RenderPasses) + fileName);

            if (jsonStream.is_open())
            {
                jsonStream >> json;
                nlohmann::json json_inputTargets = json["Input"];
                nlohmann::json json_outputPaths = json["Output"];

                Core::JsonExtract<std::string>(json, "RootLayout", m_rootLayoutPath);

                m_outputPaths = std::vector<std::string>(json_outputPaths.size());

                for (int i = 0; i < json_inputTargets.size(); i++)
                {
                    nlohmann::json json_inputTarget = json_inputTargets[i];
                    
                    InputTarget inputTarget;

                    JsonExtract<std::string>(json_inputTarget, "Path", inputTarget.path);
                    JsonExtract<uint32_t>(json_inputTarget, "Set", inputTarget.set);
                    JsonExtract<uint32_t>(json_inputTarget, "Binding", inputTarget.binding);

                    m_inputTargets.push_back(inputTarget);
                }

                for (int i = 0; i < json_outputPaths.size(); i++)
                {
                    m_outputPaths[i] = json_outputPaths[i].get<std::string>();
                }

                jsonStream.close();
                return true;
            }
            else
            {
                HT_DEBUG_PRINTF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderPasses) + fileName);
                return false;
            }
        }

        std::string RenderPass::GetRootLayoutPath() const { return m_rootLayoutPath; }
        std::vector<RenderPass::InputTarget> RenderPass::GetInputTargets() const { return m_inputTargets; }
        std::vector<std::string> RenderPass::GetOutputPaths() const { return m_outputPaths; }
    }
}
