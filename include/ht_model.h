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

#include <ht_platform.h>
#include <ht_fileresource.h>
#include <ht_mesh.h>
#include <vector>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Model : public FileResource<Model>
        {
        public:
            Model(uint64_t id);
            bool Initialize(const std::string& pPath);

        private:
            std::vector<Mesh> m_Meshes;
        };

        using ModelHandle = Handle<const Model>;
    }
}
