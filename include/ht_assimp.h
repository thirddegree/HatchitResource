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

#pragma once

#include <ht_platform.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace Hatchit {

    namespace Resource {

        HT_API void ASSIMP_MeshBounds(const aiVector3D* in, size_t size, aiVector3D& min, aiVector3D& max);

        HT_API void ASSIMP_FindMeshCenter(aiMesh* mesh, aiVector3D& out, aiVector3D& min, aiVector3D& max);


    }

}
