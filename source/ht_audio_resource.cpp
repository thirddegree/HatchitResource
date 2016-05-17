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

#include <ht_audio_resource.h>

#include <ht_file_interface.h> //Core::IFile
#include <stb_vorbis.c> //std_vorbis
#include <ht_file.h> //Core::File


namespace Hatchit
{
	namespace Resource
	{
		Audio::Audio(Core::Guid ID) : FileResource<Audio>(std::move(ID)) {}

		bool Audio::Initialize(const std::string& fileName)
		{
			m_fileName = Core::Path::Value(Core::Path::Directory::Audio) + fileName;
			int errorCode;
			stb_vorbis* oggFile = stb_vorbis_open_filename(m_fileName.c_str(), &errorCode, nullptr);
            if (!oggFile)
            {
                //Do stuff with error here
                return false;
            }
			stb_vorbis_info info = stb_vorbis_get_info(oggFile);
			m_numChannels = info.channels;
			m_sampleRate = info.sample_rate;
            m_sampleDepth = info.max_frame_size;
			m_soundLength = stb_vorbis_stream_length_in_seconds(oggFile);

            return true;
		}

		const std::string& Audio::GetFileName() const
		{
			return m_fileName;
		}

		int Audio::GetNumChannels() const
		{
			return m_numChannels;
		}

		unsigned int Audio::GetSampleRate() const
		{
			return m_sampleRate;
		}

		int Audio::GetSampleDepth() const
		{
			return m_sampleDepth;
		}

		float Audio::GetSoundLength() const
		{
			return m_soundLength;
		}
	}
}