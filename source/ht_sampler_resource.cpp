#include "ht_sampler_resource.h"

namespace Hatchit
{
    namespace Resource
    {
        Sampler::Sampler(std::string name) : FileResource<Sampler>(std::move(name)) {}

        bool Sampler::VInitFromFile(const std::string & file)
        {
            //TODO: Parse JSON file

            return true;
        }

        Sampler::FilterMode Sampler::GetFilterMode() const { return m_filterMode; }
        Sampler::WrapMode Sampler::GetWrapMode() const { return m_wrapMode; }
        Sampler::ColorSpace Sampler::GetColorSpace() const { return m_colorSpace; }
    }
}


