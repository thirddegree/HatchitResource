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
#include <ht_fileresource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Pipeline : public FileResource<Pipeline>
        {
        public:

            enum class PolygonMode
            {
                Solid,
                Line
            };

            enum class FaceWinding
            {
                CLOCKWISE,
                COUNTER_CLOCKWISE
            };

            enum class CullMode
            {
                None,
                Front,
                Back
            };

             struct DepthStencilState
            {
                bool checkDepth; //run depth test
                bool outDepth;   //write depth buffer
            };

            struct RasterState
            {
                PolygonMode polygonMode;
                CullMode    cullMode;
                FaceWinding faceWinding;
                bool        enableDepthClamp;
                bool        enablePrimitiveDiscard;
            };

            enum class SampleCount
            {
                BIT_1,
                BIT_2,
                BIT_4,
                BIT_8,
                BIT_16,
                BIT_32,
                BIT_64
            };

            struct MultisampleState
            {
                SampleCount samples;
                float       minSamples;
            };

            enum ShaderSlot
            {
                VERTEX = 0,
                FRAGMENT,
                GEOMETRY,
                TESS_CONTROL,
                TESS_EVAL,
                COMPUTE
            };
        };
    }
}