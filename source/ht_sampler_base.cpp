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

#include <ht_sampler_base.h>

namespace Hatchit
{
    namespace Resource
    {
       
     
        Sampler::ShaderVisibility Sampler::SamplerVisibilityFromString(std::string s)
        {
            Sampler::ShaderVisibility visibility;

            if (s == "ALL")
                visibility = Sampler::ShaderVisibility::ALL;
            else if (s == "VERTEX")
                visibility = Sampler::ShaderVisibility::VERTEX;
            else if (s == "TESS_CONSTROL")
                visibility = Sampler::ShaderVisibility::TESS_CONTROL;
            else if (s == "TESS_EVAL")
                visibility = Sampler::ShaderVisibility::TESS_EVAL;
            else if (s == "GEOMETRY")
                visibility = Sampler::ShaderVisibility::GEOMETRY;
            else if (s == "FRAGMENT")
                visibility = Sampler::ShaderVisibility::FRAGMENT;
            else
                visibility = Sampler::ShaderVisibility::UNKNOWN;

            return visibility;
        }

        Sampler::FilterMode Sampler::SamplerFilterModeFromString(std::string s)
        {
            Sampler::FilterMode mode = Sampler::FilterMode::NEAREST;

            if (s == "NEAREST")
                mode = Sampler::FilterMode::NEAREST;
            else if (s == "BILINEAR")
                mode = Sampler::FilterMode::BILINEAR;

            return mode;
        }

        Sampler::MipMode Sampler::SamplerMipModeFromString(std::string s)
        {
            Sampler::MipMode mode = Sampler::MipMode::LINEAR;

            if (s == "LINEAR")
                mode = Sampler::MipMode::LINEAR;
            else if (s == "NEAREST")
                mode = Sampler::MipMode::NEAREST;

            return mode;
        }

        Sampler::ColorSpace Sampler::SamplerColorSpaceFromString(std::string s)
        {
            Sampler::ColorSpace space = Sampler::ColorSpace::LINEAR;

            if (s == "LINEAR")
                space = Sampler::ColorSpace::LINEAR;
            else if (s == "GAMMA")
                space = Sampler::ColorSpace::GAMMA;

            return space;
        }

        Sampler::AddressMode Sampler::SamplerAddressModeFromString(std::string s)
        {
            Sampler::AddressMode mode = Sampler::AddressMode::CLAMP;

            if (s == "WRAP")
                mode = Sampler::AddressMode::WRAP;
            else if (s == "CLAMP")
                mode = Sampler::AddressMode::CLAMP;
            else if (s == "BORDER")
                mode = Sampler::AddressMode::BORDER;
            else if (s == "MIRROR")
                mode = Sampler::AddressMode::MIRROR;
            else if (s == "MIRROR_ONCE")
                mode = Sampler::AddressMode::MIRROR_ONCE;

            return mode;
        }

        Sampler::BorderColor Sampler::SamplerBorderColorFromString(std::string s)
        {
            Sampler::BorderColor color = Sampler::BorderColor::COLOR_OPAQUE_BLACK;

            if (s == "COLOR_OPAQUE_BLACK")
                color = Sampler::BorderColor::COLOR_OPAQUE_BLACK;
            else if (s == "COLOR_OPAQUE_WHITE")
                color = Sampler::BorderColor::COLOR_OPAQUE_WHITE;
            else if (s == "COLOR_TRANSPARENT_BLACK")
                color = Sampler::BorderColor::COLOR_TRANSPARENT_BLACK;

            return color;
        }

        Sampler::CompareOperation Sampler::SamplerCompareOpFromString(std::string s)
        {
            Sampler::CompareOperation op = Sampler::CompareOperation::COMPARE_OP_NEVER;

            if (s == "COMPARE_OP_NEVER")
                op = Sampler::CompareOperation::COMPARE_OP_NEVER;
            else if (s == "COMPARE_OP_LESS")
                op = Sampler::CompareOperation::COMPARE_OP_LESS;
            else if (s == "COMPARE_OP_EQUAL")
                op = Sampler::CompareOperation::COMPARE_OP_EQUAL;
            else if (s == "COMPARE_OP_LESS_EQUAL")
                op = Sampler::CompareOperation::COMPARE_OP_LESS_EQUAL;
            else if (s == "COMPARE_OP_GREATER")
                op = Sampler::CompareOperation::COMPARE_OP_GREATER;
            else if (s == "COMPARE_OP_NOT_EQUAL")
                op = Sampler::CompareOperation::COMPARE_OP_NOT_EQUAL;
            else if (s == "COMPARE_OP_GREATER_EQUAL")
                op = Sampler::CompareOperation::COMPARE_OP_GREATER_EQUAL;
            else if (s == "COMPARE_OP_ALWAYS")
                op = Sampler::CompareOperation::COMPARE_OP_ALWAYS;

            return op;
        }
        const Sampler::Filter & Sampler::GetFilter() const
        {
            return m_filter;
        }
        const Sampler::Address & Sampler::GetAddress() const
        {
            return m_address;
        }

        Sampler::MipMode Sampler::GetMipMode() const
        {
            return m_mipMode;
        }

        float Sampler::GetMipLODBias() const
        {
            return m_mipLODBias;
        }

        float Sampler::GetMinLOD() const
        {
            return m_minLOD;
        }

        float Sampler::GetMaxLOD() const
        {
            return m_maxLOD;
        }

        uint32_t Sampler::GetMaxAnisotropy() const
        {
            return m_maxAnisotropy;
        }

        Sampler::CompareOperation Sampler::GetCompareOp() const
        {
            return m_compareOp;
        }

        Sampler::BorderColor Sampler::GetBorderColor() const
        {
            return m_borderColor;
        }

        Sampler::ColorSpace Sampler::GetColorSpace() const
        {
            return m_colorSpace;
        }

       
    }
}