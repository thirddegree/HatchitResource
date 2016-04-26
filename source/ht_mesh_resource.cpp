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

#include <ht_mesh_resource.h>
#include <ht_debug.h>
#include <iterator>

namespace Hatchit {

    namespace Resource {

        Mesh::Mesh(aiMesh* mesh)
        {
            std::copy(mesh->mVertices, mesh->mVertices + mesh->mNumVertices, std::back_inserter(m_vertices));
            if(mesh->HasNormals())
                std::copy(mesh->mNormals, mesh->mNormals + mesh->mNumVertices, std::back_inserter(m_normals));
            if(mesh->HasTextureCoords(0))
                std::copy(mesh->mTextureCoords[0], mesh->mTextureCoords[0] + mesh->mNumVertices, std::back_inserter(m_uvs));

            std::copy(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, std::back_inserter(m_indices));
        }

        Mesh::~Mesh()
        {

        }

        std::vector<aiVector3D> Mesh::getVertices() { return m_vertices; }
        std::vector<aiVector3D> Mesh::getNormals() { return m_normals; }
        std::vector<aiVector3D> Mesh::getUVs() { return m_uvs; }

        std::vector<aiFace> Mesh::getIndices() { return m_indices; }
    }
}