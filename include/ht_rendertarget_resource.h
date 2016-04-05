#pragma once

#include <ht_resource.h>

namespace Hatchit {

    namespace Resource {

        class HT_API RenderTarget : public Resource<RenderTarget>
        {
        public:
            RenderTarget(std::string filename);
            virtual ~RenderTarget() = default;

            virtual bool VInitFromFile(const std::string& filename) override;

        private:
            uint32_t m_width;
            uint32_t m_height;
            std::string m_format;
        };

        using RenderTargetHandle = Handle<RenderTarget>;
    }
}