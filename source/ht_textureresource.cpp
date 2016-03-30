#include <ht_textureresource.h>
#include <ht_image.h>

namespace Hatchit
{
    namespace Resource
    {
        Texture::Texture(std::string name) : Resource(std::move(name)) {}

        bool Texture::VInitFromFile(const std::string& file)
        {
            Core::File f;
            f.Open(Core::os_exec_dir() + file, Core::FileMode::ReadBinary);

            Image* bitmap = Image::Load(&f, Image::Channels::AUTO);

            m_width = bitmap->GetWidth();
            m_height = bitmap->GetHeight();
            m_mipLevels = 1;

            m_bpp = static_cast<uint8_t>(bitmap->GetBPP());
            m_channels = static_cast<uint32_t>(bitmap->GetChannels());

            m_data = bitmap->GetData();

            return true;
        }

        uint32_t Texture::GetWidth() const
        {
            return m_width;
        }

        uint32_t Texture::GetHeight() const
        {
            return m_height;
        }

        uint8_t Texture::GetChannels() const
        {
            return m_channels;
        }

        uint32_t Texture::GetMIPLevels() const
        {
            return m_mipLevels;
        }

        const BYTE* Texture::GetData() const
        {
            return m_data;
        }
    }
}