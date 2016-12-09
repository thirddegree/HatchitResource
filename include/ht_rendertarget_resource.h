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
        class HT_API RenderTarget : public FileResource<RenderTarget>
        {
        public:
            RenderTarget(uint64_t id);

            ~RenderTarget();

            bool Initialize(const std::string& path);

            enum class BlendOp
            {
                Add,
                Sub,
                RevSub,
                Min,
                Max,
                None
            };

            struct Color
            {
                float r, g, b, a;
            };
        private:
            uint32_t        m_width;
            uint32_t        m_height;
            std::string     m_format;
            Color           m_clear;
            BlendOp         m_colorOp;
            BlendOp         m_alphaOp;

            BlendOp GetBlendOpFromString(const std::string& op);
        };
    }
}