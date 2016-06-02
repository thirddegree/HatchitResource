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

#include <ht_scene_resource.h>
#include <ht_path_singleton.h>
#include <ht_file.h>
#include <ht_debug.h>
#include <ht_file_exception.h>

#include <stdexcept>

namespace Hatchit
{
    namespace Resource
    {
        Scene::Scene(Core::Guid ID) : FileResource<Scene>(std::move(ID)) {}

        bool Scene::Initialize(const std::string& fileName)
        {
            try
            {
                Core::File f;
                std::string file_contents;

                f.Open(Core::Path::Value(Core::Path::Directory::Scenes) + fileName, Core::File::FileMode::ReadText);

                file_contents.resize(f.SizeBytes());
                f.Read(reinterpret_cast<BYTE*>(&file_contents[0]), file_contents.size());

                m_sceneDescription = nlohmann::json::parse(file_contents);
            }
            catch (Core::FileException e)
            {
                HT_DEBUG_PRINTF("There was a problem accessing JSON file %s!\nError: %s\n", fileName, e.what());
                return false;
            }
            catch (std::invalid_argument e)
            {
                HT_DEBUG_PRINTF("There was a problem parsing JSON file %s!\nError: %s\n", fileName, e.what());
                return false;
            }
            return true;
        }

        bool Scene::VInitFromFile(const std::string& file)
        {
            try
            {
                Core::File f;
                std::string file_contents;

                f.Open(Core::Path::Value(Core::Path::Directory::Scenes) + file, Core::File::FileMode::ReadText);

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