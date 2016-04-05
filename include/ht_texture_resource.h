#pragma once
#include <ht_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        class HT_API Texture : public Resource<Texture>
        {
        public:
            Texture(std::string name);
            virtual ~Texture() = default;

            bool VInitFromFile(const std::string& file) override;

            uint32_t GetWidth() const;
            uint32_t GetHeight() const;

            uint32_t GetMIPLevels() const;

            uint8_t GetChannels() const;

            const BYTE* GetData() const;


        private:
            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_mipLevels;
            uint8_t m_bpp;
            uint8_t m_channels;

            const BYTE* m_data;
        };

        using TextureHandle = Handle<Texture>;
    }
}