#include <ht_texture_resource.h>
#include <ht_image.h>
#include <ht_path_singleton.h>

namespace Hatchit
{
    namespace Resource
    {
        Texture::Texture(std::string ID, const std::string& fileName) : FileResource<Texture>(std::move(ID))
        {
            Core::File f;
            f.Open(Core::Path::Value(Core::Path::Directory::Textures) + fileName, Core::FileMode::ReadBinary);

            Image* bitmap = Image::Load(&f, Image::Channels::AUTO);

            m_width = bitmap->GetWidth();
            m_height = bitmap->GetHeight();
            m_mipLevels = 1;

            m_bpp = static_cast<uint8_t>(bitmap->GetBPP());
            m_channels = static_cast<uint32_t>(bitmap->GetChannels());

            m_data = bitmap->GetData();
        }

        bool Texture::VInitFromFile(const std::string& file)
        {
            Core::File f;
            f.Open(Core::Path::Value(Core::Path::Directory::Textures) + file, Core::FileMode::ReadBinary);

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