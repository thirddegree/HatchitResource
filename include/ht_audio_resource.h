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

#include <ht_platform.h> //HT_API
#include <ht_resource.h> //FileResource<T>

namespace Hatchit
{
	namespace Resource
	{
		class HT_API Audio final : public FileResource<Audio>
		{
		public:
			Audio(Core::Guid ID);
			virtual ~Audio() = default;

			//Required function for all RefCounted classes
			bool Initialize(const std::string& fileName);

			const std::string& GetFileName() const;
			int GetNumChannels() const;
			unsigned int GetSampleRate() const;
			int GetSampleDepth() const;
			float GetSoundLength() const;

		private:
			std::string m_fileName;
			int m_numChannels;
			unsigned int m_sampleRate;
			int m_sampleDepth;
			float m_soundLength;
		};

		using AudioResourceHandle = Core::Handle<const Audio>;
	}
}