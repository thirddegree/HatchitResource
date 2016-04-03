#include <ht_rendertarget_resource.h>

namespace Hatchit {

    namespace Resource {

        using namespace Core;

        RenderTarget::RenderTarget(std::string filename) : Resource(std::move(filename)) 
        {
        }

        bool RenderTarget::VInitFromFile(const std::string& filename)
        {
            nlohmann::json json;
            std::ifstream jsonStream(Path::Value(Path::Directory::RenderTargets) + filename);

            if (jsonStream.is_open())
            {
                jsonStream >> json;

                JsonExtractUint32(json, "Width", m_width);
                JsonExtractUint32(json, "Height", m_height);
                JsonExtractString(json, "Format", m_format);

                jsonStream.close();
                return true;
            }

            DebugPrintF("ERROR: Could not generate stream to JSON file -> %s", Path::Value(Path::Directory::RenderTargets) + filename);
            return false;
        }
    }
}