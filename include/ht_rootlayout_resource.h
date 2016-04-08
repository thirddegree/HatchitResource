/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 ThirdDegree
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

#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API RootLayout : public FileResource<RootLayout>
        {
        public:

            enum RootDescriptorFlags
            {
                DESCRIPTOR_FLAG_NONE = 0,
                DESCRIPTOR_ALLOW_INPUT_ASSEMLBER_INPUT_LAYOUT,
                DESCRIPTOR_DENY_VERTEX_SHADER_ROOT_ACCESS,
                DESCRIPTOR_DENY_TESSELATION_CONTROL_SHADER_ROOT_ACCESS,
                DESCRIPTOR_DENY_TESSELATION_EVAL_SHADER_ROOT_ACCESS,
                DESCRIPTOR_DENY_GEOMETRY_SHADER_ROOT_ACCESS,
                DESCRIPTOR_DENY_FRAGMENT_SHADER_ROOT_ACCESS0,
                DESCRIPTOR_ALLOW_STREAM_OUTPUT
            };

            struct Range
            {
                enum class Type
                {
                    UKNOWN,
                    CONSTANT_BUFFER,
                    SHADER_RESOURCE,
                    UNORDERED_ACCESS,
                    SAMPLER
                };

                Type		type;
                uint32_t	numDescriptors;
                uint32_t	baseRegister;
                uint32_t	registerSpace;
            };

            struct DescriptorTable
            {
                uint32_t			rangeCount;
                std::vector<Range>	ranges;
            };

            struct Constant
            {
                uint32_t shaderRegister;
                uint32_t registerSpace;
                uint32_t valueCount;
            };

            struct Descriptor
            {
                uint32_t shaderRegister;
                uint32_t registerSpace;
            };

            struct Parameter
            {
                struct Data
                {
                    DescriptorTable table;
                    Constant		constant;
                    Descriptor	    descriptor;
                };

                enum class Type
                {
                    UNKNOWN,
                    TABLE,
                    CONSTANT,
                    CONSTANT_BUFFER,
                    SHADER_RESOURCE,
                    UNORDERED_ACCESS
                };

                enum class Visibility
                {
                    UNKNOWN,
                    ALL,
                    VERTEX,
                    TESS_CONTROL,
                    TESS_EVAL,
                    GEOMETRY,
                    FRAGMENT
                };

                Type			type;
                Visibility		visibility;
                Data			data;
            };

            RootLayout(std::string ID, const std::string& fileName);

            virtual ~RootLayout() = default;


            uint32_t                        GetParameterCount() const;
            RootDescriptorFlags             GetDescriptorFlags() const;
            const std::vector<Parameter>&   GetParameters() const;

            virtual bool VInitFromFile(const std::string& fileName);

        private:
            uint32_t                m_parameterCount;
            std::vector<Parameter>  m_parameters;
            RootDescriptorFlags     m_flags;


            Parameter::Visibility   ParameterVisibilityFromString(std::string s);
            Parameter::Type			ParameterTypeFromString(std::string s);
            Range::Type				RangeTypeFromString(std::string s);
        };

        using RootLayoutHandle = Core::Handle<const RootLayout>;
    }
}