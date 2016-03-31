#include "ht_sampler_resource.h"

namespace Hatchit
{
    namespace Resource
    {
        Sampler::Sampler(std::string name) : Resource(std::move(name)) {}

        bool Sampler::VInitFromFile(const std::string & file)
        {
            //TODO: Parse JSON file

            return true;
        }
    }
}


