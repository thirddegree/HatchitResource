
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

#include <ht_model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Hatchit
{
    namespace Resource
    {
        Model::Model(uint64_t id)
            : FileResource<Model>(std::move(id))
        {
        }

        bool Model::Initialize(const std::string &pPath)
        {
            Assimp::Importer pImporter{};

            const aiScene* pScene = pImporter.ReadFile(pPath, aiProcess_CalcTangentSpace);

            if ( pScene == nullptr )
            {
                HT_ERROR_PRINTF("Model::Initialize(): Failed to load model file.\n");
                return false;
            }

            if (!pScene->HasMeshes())
            {
                HT_ERROR_PRINTF("Model::Initialize(): File has no meshes in it.\n");
                return false;
            }

            for ( size_t i = 0; i < pScene->mNumMeshes; i++ )
            {
                Mesh pMesh{*pScene->mMeshes[i]};

                m_Meshes.push_back(pMesh);
            }

            return true;
        }
    }
}
