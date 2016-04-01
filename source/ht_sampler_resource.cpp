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

        Sampler::FilterMode Sampler::GetFilterMode() { return m_filterMode; }
        Sampler::WrapMode Sampler::GetWrapMode() { return m_wrapMode; }
        Sampler::ColorSpace Sampler::GetColorSpace() { return m_colorSpace; }
    }
}


