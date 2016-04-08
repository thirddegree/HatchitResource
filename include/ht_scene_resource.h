/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
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

#include <ht_resource.h>

#include <json.hpp>

#include <string>

namespace Hatchit {
    namespace Resource {
        class HT_API Scene : public FileResource<Scene>
        {
        public:
            Scene(std::string ID, const std::string& fileName);
            virtual ~Scene(void) = default;
            Scene(Scene&& rhs) = default;
            Scene& operator=(Scene&& rhs) = default;

            virtual bool VInitFromFile(const std::string& file) override;

            const nlohmann::json& GetSceneDescription(void) const;
        private:
            nlohmann::json m_sceneDescription;
        };

        using SceneHandle = Core::Handle<const Scene>;
    }
}
