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

        Model::Model(std::string ID, const std::string& fileName) : FileResource<Model>(std::move(ID)) 
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
#ifdef _DEBUG
                Core::DebugPrintF("ASSIMP READ ERROR: %s\n", _importer.GetErrorString());
#endif
                return;
            }

#ifdef _DEBUG
            Core::DebugPrintF("Assimp Load [%s]\n", fileName);
            Core::DebugPrintF("[#Meshes]: \t%d\n", scene->mNumMeshes);
            Core::DebugPrintF("[#Materials]: \t%d\n", scene->mNumMaterials);
#endif
            //Load Mesh Data
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[i];

#ifdef _DEBUG
                Core::DebugPrintF("[Mesh#%d]:\n", i);
                Core::DebugPrintF("\t[#Vertices]: \t%d\n", mesh->mNumVertices);
                Core::DebugPrintF("\t[#Faces]: \t%d\n", mesh->mNumFaces);
                Core::DebugPrintF("\t[#Bones]: \t%d\n", mesh->mNumBones);
#endif
                m_meshes.push_back(new Mesh(mesh));
            }
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
#ifdef _DEBUG
                Core::DebugPrintF("ASSIMP READ ERROR: %s\n", _importer.GetErrorString());
#endif
                return false;
            }            
            
#ifdef _DEBUG
            Core::DebugPrintF("Assimp Load [%s]\n", file);
            Core::DebugPrintF("[#Meshes]: \t%d\n", scene->mNumMeshes);
            Core::DebugPrintF("[#Materials]: \t%d\n", scene->mNumMaterials);
#endif
            //Load Mesh Data
            for (uint32_t i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[i];

#ifdef _DEBUG
                Core::DebugPrintF("[Mesh#%d]:\n", i);
                Core::DebugPrintF("\t[#Vertices]: \t%d\n", mesh->mNumVertices);
                Core::DebugPrintF("\t[#Faces]: \t%d\n", mesh->mNumFaces);
                Core::DebugPrintF("\t[#Bones]: \t%d\n", mesh->mNumBones);
#endif
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

