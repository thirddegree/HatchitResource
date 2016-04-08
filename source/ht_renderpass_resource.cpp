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
namespace Hatchit
{
    namespace Resource
    {
        using namespace Core;

        RenderPass::RenderPass(std::string name) : FileResource<RenderPass>(std::move(name)) {}

        bool RenderPass::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::RenderPasses) + filename);

            if (jsonStream.is_open())
            {
                jsonStream >> json;
                nlohmann::json json_inputPaths = json["Input"];
                nlohmann::json json_outputPaths = json["Output"];
                m_inputPaths = std::vector<std::string>(json_inputPaths.size());
                m_outputPaths = std::vector<std::string>(json_outputPaths.size());

                for (int i = 0; i < json_inputPaths.size(); i++)
                {
                    m_inputPaths[i] = json_inputPaths[i].get<std::string>();
                }

                for (int i = 0; i < json_outputPaths.size(); i++)
                {
                    m_outputPaths[i] = json_outputPaths[i].get<std::string>();
                }

                jsonStream.close();
                return true;
            }

            DebugPrintF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderPasses) + filename);
            return false;
        }

        std::vector<std::string> RenderPass::GetInputPaths() const { return m_inputPaths; }
        std::vector<std::string> RenderPass::GetOutputPaths() const { return m_outputPaths; }
    }
}