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

#include <ht_shader_resource.h>
#include <ht_path_singleton.h>

namespace Hatchit {

    namespace Resource {

        Shader::Shader(std::string ID) : FileResource<Shader>(std::move(ID)), m_bytecode(nullptr), m_bytecodeSize(0) {}

        bool Shader::Initialize(const std::string& fileName)
        {
            if (fileName.empty())
                return false;

            Core::File file;
            try
            {
                file.Open(Core::Path::Value(Core::Path::Directory::Shaders) + fileName, Core::FileMode::ReadBinary);
            }
            catch (std::exception)
            {
                HT_DEBUG_PRINTF("Failed to open Shader file: %s\n", fileName);
                return false;
            }

            m_bytecodeSize = file.SizeBytes();
            assert(m_bytecodeSize != 0);
            if (m_bytecodeSize == 0)
                return false;

            m_bytecode = new BYTE[m_bytecodeSize]; //Can't create new void* but we can create BYTEs

            file.Read(m_bytecode, m_bytecodeSize);

            return true;
        }
        Shader::~Shader() 
        {
            delete[] m_bytecode;
        }

        bool Shader::VInitFromFile(const std::string& filename) 
        {
            if (filename.empty())
                return false;

            Core::File file;
            try
            {
                file.Open(Core::Path::Value(Core::Path::Directory::Shaders) + filename, Core::FileMode::ReadBinary);
            }
            catch (std::exception)
            {
                HT_DEBUG_PRINTF("Failed to open Shader file: %s\n", filename);
                return false;
            }
            
            m_bytecodeSize = file.SizeBytes();
            assert(m_bytecodeSize != 0);
            if (m_bytecodeSize == 0)
                return false;

            m_bytecode = new BYTE[m_bytecodeSize]; //Can't create new void* but we can create BYTEs

            file.Read(m_bytecode, m_bytecodeSize);

            return true;
        }

        const BYTE* Shader::GetBytecode() const { return m_bytecode; }
        size_t Shader::GetBytecodeSize() const { return m_bytecodeSize; }
    }

}