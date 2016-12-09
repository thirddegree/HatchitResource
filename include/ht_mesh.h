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
#include <ht_vertex.h>
#include <assimp/mesh.h>
#include <vector>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Mesh
        {
        public:
          Mesh(const aiMesh& pMesh);
          private:
          std::vector<Hatchit::Graphics::Vertex> m_Vertex;
        };
    };
}
