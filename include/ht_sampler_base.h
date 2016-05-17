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
#include <ht_types.h>
#include <ht_string.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Sampler
        {
        public:
            enum class ShaderVisibility
            {
                UNKNOWN,
                ALL,
                VERTEX,
                TESS_CONTROL,
                TESS_EVAL,
                GEOMETRY,
                FRAGMENT
            };

            struct Immutable
            {
                uint32_t            shaderRegister;
                uint32_t            registerSpace;
                ShaderVisibility    visibility;
            };

            enum class AddressMode
            {
                WRAP,
                CLAMP,
                BORDER,
                MIRROR,
                MIRROR_ONCE
            };

            enum class CompareOperation
            {
                COMPARE_OP_NEVER,
                COMPARE_OP_LESS,
                COMPARE_OP_EQUAL,
                COMPARE_OP_LESS_EQUAL,
                COMPARE_OP_GREATER,
                COMPARE_OP_NOT_EQUAL,
                COMPARE_OP_GREATER_EQUAL,
                COMPARE_OP_ALWAYS
            };

            enum class FilterMode
            {
                NEAREST,
                BILINEAR
            };

            enum class MipMode
            {
                NEAREST,
                LINEAR
            };

            enum class BorderColor
            {
                COLOR_TRANSPARENT_BLACK,
                COLOR_OPAQUE_BLACK,
                COLOR_OPAQUE_WHITE
            };

            enum class ColorSpace
            {
                GAMMA,
                LINEAR
            };

            struct Address
            {
                AddressMode u;
                AddressMode v;
                AddressMode w;
            };

            struct Filter
            {
                FilterMode min;
                FilterMode mag;
            };

            virtual ~Sampler() = default;

            const Filter&      GetFilter() const;
            const Address&     GetAddress() const;
            const Immutable&   GetImmutable() const;
            float              GetMipLODBias() const;
            float              GetMinLOD() const;
            float              GetMaxLOD() const;
            uint32_t           GetMaxAnisotropy() const;
            CompareOperation   GetCompareOp() const;
            BorderColor        GetBorderColor() const;
            ColorSpace         GetColorSpace() const;
            MipMode            GetMipMode() const;

        protected:
            Address             m_address;
            Filter              m_filter;
            float               m_mipLODBias;
            float               m_minLOD;
            float               m_maxLOD;
            uint32_t            m_maxAnisotropy;
            CompareOperation    m_compareOp;
            BorderColor         m_borderColor;
            MipMode             m_mipMode;
            Immutable           m_immutable;
            ColorSpace          m_colorSpace;


            static Sampler::MipMode            SamplerMipModeFromString(std::string s);
            static Sampler::FilterMode         SamplerFilterModeFromString(std::string s);
            static Sampler::AddressMode        SamplerAddressModeFromString(std::string s);
            static Sampler::ColorSpace         SamplerColorSpaceFromString(std::string s);
            static Sampler::CompareOperation   SamplerCompareOpFromString(std::string s);
            static Sampler::BorderColor        SamplerBorderColorFromString(std::string s);
            static ShaderVisibility	           SamplerVisibilityFromString(std::string s);

            friend class RootLayout;

        };
    }
}