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

#include <ht_assimp.h>

namespace Hatchit {

    namespace Resource {

        void ASSIMP_MeshBounds(const aiVector3D* in, size_t size, aiVector3D& min, aiVector3D& max)
        {
            min = in[0];
            max = in[0];
            for(size_t i = 0; i < size; i++) {
                min.x = std::min(in[i].x, min.x);
                min.y = std::min(in[i].y, min.y);
                min.z = std::min(in[i].z, min.z);

                max.x = std::max(in[i].x, max.x);
                max.y = std::max(in[i].y, max.y);
                max.z = std::max(in[i].z, max.z);
            }
        }

        void ASSIMP_FindMeshCenter(aiMesh* mesh, aiVector3D& out, aiVector3D& min, aiVector3D& max)
        {
            ASSIMP_MeshBounds(mesh->mVertices, mesh->mNumVertices, min, max);

            out = (min + max) * 0.5f;
        }

    }

}
