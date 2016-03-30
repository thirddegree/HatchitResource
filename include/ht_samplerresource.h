#pragma once

#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Sampler : public Resource<Sampler>
        {
        public:
            //Enums
            enum WrapMode
            {
                REPEAT,
                CLAMP
            };

            enum FilterMode
            {
                NEAREST,
                BILINEAR
            };

            enum ColorSpace
            {
                GAMMA,
                LINEAR
            };

            Sampler(std::string name);
            virtual ~Sampler() = default;

            // Inherited via Resource
            virtual bool VInitFromFile(const std::string & file) override;

            FilterMode m_filterMode;
            WrapMode m_wrapMode;
            ColorSpace m_colorSpace;
        };

        using SamplerHandle = Sampler::Handle;
    }
}