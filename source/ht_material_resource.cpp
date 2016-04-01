#include <ht_material_resource.h>

namespace Hatchit
{
    namespace Resource
    {
        Material::Material(std::string name) : Resource(std::move(name)) {}

        bool Material::VInitFromFile(const std::string& file)
        {
            //TODO: Insert implementation for Material JSON parse
            return true;
        }
    }
}