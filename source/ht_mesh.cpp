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

#include <ht_mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <glm/vec3.hpp>

namespace Hatchit
{
    namespace Resource
    {
        Mesh::Mesh(const aiMesh& pMesh)
        {
            for ( size_t i = 0; i < pMesh.mNumVertices; i++ )
            {
                glm::vec3 pPosition{pMesh.mVertices[i].x, pMesh.mVertices[i].y, pMesh.mVertices[i].z};
                glm::vec3 pNormal{pMesh.mNormals[i].x, pMesh.mNormals[i].y, pMesh.mNormals[i].z};
                glm::vec3 pColor{0.f, 0.f, 0.f};

                Hatchit::Graphics::Vertex pVertex{pPosition, pNormal, pColor};

                m_Vertex.push_back(pVertex);
            }
        }
    }
}
