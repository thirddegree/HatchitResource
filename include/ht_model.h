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

#include <ht_platform.h>
#include <ht_resource.h>
#include <ht_file.h>
#include <ht_mesh_resource.h>

namespace Hatchit {

    namespace Resource {

        class HT_API Model : public FileResource<Model>
        {
        public:
            Model(std::string ID, const std::string& fileName);

            virtual ~Model() = default;
        
			bool VInitFromFile(const std::string& file) override;

            const std::vector<Mesh*>& GetMeshes() const;
        private:
            std::vector<Mesh*> m_meshes;

        };

        using ModelHandle = Core::Handle<const Model>;
    }
}
