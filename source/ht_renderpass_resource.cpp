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

#include <ht_renderpass_resource.h>
#include <ht_jsonhelper.h>
#include <ht_file.h>
#include <ht_file_exception.h>

namespace Hatchit
{
    namespace Resource
    {
        RenderPass::RenderPass(uint64_t id)
            : FileResource<RenderPass>(id)
        {

        }

        RenderPass::~RenderPass()
        {

        }

        bool RenderPass::Initialize(const std::string& path)
        {
            using namespace Core;

            try
            {
                File file;
                file.Open(path, File::FileMode::ReadBinary);

                JSON j;
                *file.Handle() >> j;
                
                JsonExtract<std::string>(j, "Layout", m_layout);
                JsonExtractContainer(j, "Output", m_outputs);

                JSON inputs = j["Input"];
                for (auto& i : inputs)
                {
                    Input target;
                    JsonExtract(i, "Path", target.path);
                    JsonExtract(i, "Set", target.set);
                    JsonExtract(i, "Binding", target.binding);

                    m_inputs.push_back(target);
                }

            }
            catch (const FileException& e)
            {
                HT_ERROR_PRINTF("%s\n", e.what());
                return false;
            }
            

            return true;
        }

        const std::string& RenderPass::GetLayout() const
        {
            return m_layout;
        }

        const std::vector<RenderPass::Input>& RenderPass::GetInputs() const
        {
            return m_inputs;
        }

        const std::vector<std::string>& RenderPass::GetOutputs() const
        {
            return m_outputs;
        }
    }
}