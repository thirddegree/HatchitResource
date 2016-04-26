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
#include <ht_assimp.h>
#include <vector>
#include <memory>

namespace Hatchit {

    namespace Resource {

        class HT_API Mesh
        {
        public:
            Mesh(aiMesh* mesh);

            ~Mesh();

            std::vector<aiVector3D> getVertices();
            std::vector<aiVector3D> getNormals();
            std::vector<aiVector3D> getUVs();

            std::vector<aiFace> getIndices();

        private:
            std::vector<aiVector3D> m_vertices;
            std::vector<aiVector3D> m_normals;
            std::vector<aiVector3D> m_uvs;

            std::vector<aiFace>     m_indices;
        };
        typedef std::unique_ptr<Mesh> MeshPtr;
    }
}