#pragma once

#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Sampler : public FileResource<Sampler>
        {
        public:
            //Enums
            enum WrapMode
            {
                WRAP,
                CLAMP,
                BORDER,
                MIRROR,
                MIRROR_ONCE
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

            FilterMode GetFilterMode() const;
            WrapMode GetWrapMode() const;
            ColorSpace GetColorSpace() const;

        private:
            FilterMode m_filterMode;
            WrapMode m_wrapMode;
            ColorSpace m_colorSpace;
        };

        using SamplerHandle = Core::Handle<const Sampler>;
    }
}