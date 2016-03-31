/**
**    Hatchit Engine
**    Copyright(c) 2015 ThirdDegree
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

/**
* \class Pipeline
* \ingroup HatchitResource
*
* \brief A Pipeline resource object described by JSON
*
* This loads a Pipeline JSON object from a file and sorts its data into fields
* for the HatchitGraphics IPipeline and its derivatives to implement. 
* Shaders described here will be loaded by graphics.
*/

#pragma once

#include <ht_debug.h>
#include <ht_platform.h>
#include <ht_resource.h>
#include <ht_guid.h>
#include <ht_jsonhelper.h>
#include <ht_shadervariable.h>
#include <ht_math.h>

#include <fstream>

namespace Hatchit {

    namespace Resource {

        class HT_API Pipeline : public Resource<Pipeline>
        {
        public:
            enum PolygonMode
            {
                SOLID,
                LINE
            };

            enum CullMode
            {
                NONE,
                FRONT,
                BACK
            };

            //Describes options for the render state
            //Some options are not available such as front face winding order
            struct RasterizerState
            {
                PolygonMode polygonMode;           //How we want to render objects
                CullMode    cullMode;              //How we want to cull faces
                bool        frontCounterClockwise; //Determines if a triangle is front- or back-facing.
                bool        depthClampEnable;      //True to use depth clamping, false to clip primitives
                bool        discardEnable;         //True to discard primitives before rasterization
                float       lineWidth;             //How wide to render when using Line polygon mode
            };

            enum SampleCount
            {
                SAMPLE_1_BIT,
                SAMPLE_2_BIT,
                SAMPLE_4_BIT,
                SAMPLE_8_BIT,
                SAMPLE_16_BIT,
                SAMPLE_32_BIT,
                SAMPLE_64_BIT
            };

            //Describes the multisampling state of the pipeline
            struct MultisampleState
            {
                SampleCount samples;	        //How many bits per sample
                float       minSamples;		    //Min samples per fragment
                bool        perSampleShading;   //Shades per sample if true, per fragment if false
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

            Pipeline(std::string name);
            virtual ~Pipeline() = default;
            bool VInitFromFile(const std::string& filename) override;

            RasterizerState GetRasterizationState();
            MultisampleState GetMultisampleState();

            std::map<std::string, ShaderVariable*> GetShaderVariables();
            std::map<ShaderSlot, std::string> GetShaderPaths();

        private:
            RasterizerState     m_rasterizationState;
            MultisampleState    m_multisampleState;

            std::map<std::string, ShaderVariable*>   m_shaderVariables;

            std::map<ShaderSlot, std::string> m_shaderPaths;
        };


        using PipelineHandle = Pipeline::Handle;
    }

}