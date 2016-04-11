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

#include <ht_model.h>
#include <ht_assimp.h>
#include <ht_debug.h>
#include <ht_path_singleton.h>

namespace Hatchit {

    namespace Resource {

        Model::Model(std::string ID) : FileResource<Model>(std::move(ID)) {}

        bool Model::Initialize(const std::string& fileName)
        {
            Assimp::Importer _importer;

            const aiScene* scene = _importer.ReadFile(Core::Path::Value(Core::Path::Directory::Models) + fileName,
                aiProcess_CalcTangentSpace |
                aiProcess_Triangulate |
                aiProcess_GenNormals |
                aiProcess_JoinIdenticalVertices |
                aiProcess_SortByPType |
                aiProcess_GenUVCoords |
                aiProcess_TransformUVCoords |
                aiProcess_FlipUVs);
            if (!scene)
            {
                HT_DEBUG_PRINTF("ASSIMP READ ERROR: %s\n", _importer.GetErrorString());
                return false;
            }

            HT_DEBUG_PRINTF("Assimp Load [%s]\n", fileName);
            HT_DEBUG_PRINTF("[#Meshes]: \t%d\n", scene->mNumMeshes);
            HT_DEBUG_PRINTF("[#Materials]: \t%d\n", scene->mNumMaterials);

            //Load Mesh Data
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[i];

                HT_DEBUG_PRINTF("[Mesh#%d]:\n", i);
                HT_DEBUG_PRINTF("\t[#Vertices]: \t%d\n", mesh->mNumVertices);
                HT_DEBUG_PRINTF("\t[#Faces]: \t%d\n", mesh->mNumFaces);
                HT_DEBUG_PRINTF("\t[#Bones]: \t%d\n", mesh->mNumBones);

                m_meshes.push_back(new Mesh(mesh));
            }

            return true;
        }

        bool Model::VInitFromFile(const std::string& file)
        {
            Assimp::Importer _importer;
            
            const aiScene* scene = _importer.ReadFile(Core::Path::Value(Core::Path::Directory::Models) + file,
                aiProcess_CalcTangentSpace |
                aiProcess_Triangulate |
                aiProcess_GenNormals |
                aiProcess_JoinIdenticalVertices |
                aiProcess_SortByPType |
                aiProcess_GenUVCoords |
                aiProcess_TransformUVCoords |
                aiProcess_FlipUVs);
            if(!scene)
            {
                HT_DEBUG_PRINTF("ASSIMP READ ERROR: %s\n", _importer.GetErrorString());
                return false;
            }            
            
            HT_DEBUG_PRINTF("Assimp Load [%s]\n", file);
            HT_DEBUG_PRINTF("[#Meshes]: \t%d\n", scene->mNumMeshes);
            HT_DEBUG_PRINTF("[#Materials]: \t%d\n", scene->mNumMaterials);

            //Load Mesh Data
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[i];

                HT_DEBUG_PRINTF("[Mesh#%d]:\n", i);
                HT_DEBUG_PRINTF("\t[#Vertices]: \t%d\n", mesh->mNumVertices);
                HT_DEBUG_PRINTF("\t[#Faces]: \t%d\n", mesh->mNumFaces);
                HT_DEBUG_PRINTF("\t[#Bones]: \t%d\n", mesh->mNumBones);

                m_meshes.push_back(new Mesh(mesh));
            }

            return true;
        }

        const std::vector<Mesh*>& Model::GetMeshes() const
        {
            return m_meshes;
        }

    }
}

