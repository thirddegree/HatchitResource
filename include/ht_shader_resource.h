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

#include <ht_platform.h>
#include <ht_resource.h>
#include <ht_debug.h>
#include <fstream>

#pragma once

namespace Hatchit {

    namespace Resource {
    
        class HT_API Shader : public Resource<Shader>
        {
        public:
            Shader(std::string name);
            ~Shader();

            bool VInitFromFile(const std::string& filename) override;

            BYTE* GetBytecode();
            size_t GetBytecodeSize();

        private:
            BYTE* m_bytecode;
            size_t m_bytecodeSize;
        };

        using ShaderHandle = Shader::Handle;

    }

}