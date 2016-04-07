#include <ht_scene_resource.h>
#include <ht_path_singleton.h>
#include <ht_file.h>
#include <ht_debug.h>

#include <stdexcept>

namespace Hatchit {
    namespace Resource {
        Scene::Scene(std::string name) : FileResource<Scene>(std::move(name)){}

        bool Scene::VInitFromFile(const std::string& file)
        {
            try
            {
                Core::File f;
                std::string file_contents;

                f.Open(Core::Path::Value(Core::Path::Directory::Scenes) + file, Core::FileMode::ReadText);

                file_contents.resize(f.SizeBytes());
                f.Read(reinterpret_cast<BYTE*>(&file_contents[0]), file_contents.size());

                m_sceneDescription = nlohmann::json::parse(file_contents);
            }
            catch (Core::FileException e)
            {
                HT_DEBUG_PRINTF("There was a problem accessing JSON file %s!\nError: %s\n", file, e.what());
                return false;
            }
            catch (std::invalid_argument e)
            {
                HT_DEBUG_PRINTF("There was a problem parsing JSON file %s!\nError: %s\n", file, e.what());
                return false;
            }

            return true;
        }

        const nlohmann::json& Scene::GetSceneDescription(void) const
        {
            return m_sceneDescription;
        }
    }
}