#include "Sound.h"

#include <AL/al.h>
#include <AL/alext.h>
#include <sndfile.h>
#include "SoundManager.h"
#include "Error.h"

std::map<std::string, Sound*> SoundManager::s_sounds;

Sound::Sound() : m_buffer(0)
{
}

Sound::~Sound()
{
	m_buffer = 0;
}

void Sound::LoadFromWav(const char* filename)
{
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t numFrames;
	ALsizei numBytes;

	sndfile = sf_open(filename, SFM_READ, &sfinfo);
	if(!sndfile)
	{
		Error::FileLog("Could not open audio in " + std::string(filename ) + ": " + sf_strerror(sndfile));
		return;
	}

	if(sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		Error::FileLog("Bad sample count in " + std::string(filename));
		sf_close(sndfile);
		return;
	}

	format = AL_NONE;
	if(sfinfo.channels == 1)
		format = AL_FORMAT_MONO16;
	else if(sfinfo.channels == 2)
		format = AL_FORMAT_STEREO16;
	else if(sfinfo.channels == 3)
	{
		if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
	}
	else if(sfinfo.channels == 4)
	{
		if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
	}
	if(!format)
	{
		Error::FileLog("Unsupported channel count: " + sfinfo.channels);
		sf_close(sndfile);
		return;
	}

	membuf = static_cast<short*>(malloc((size_t) (sfinfo.frames * sfinfo.channels) * sizeof(short)));

	numFrames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if(numFrames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		Error::FileLog("Failed to read samples in " + std::string(filename));
		return;
	}

	numBytes = (ALsizei) (numFrames * sfinfo.channels) * (ALsizei) sizeof(short);

	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, numBytes, sfinfo.samplerate);
	
	free(membuf);
	sf_close(sndfile);

	err = alGetError();
	if(err != AL_NO_ERROR)
	{
		Error::FileLog("OpenAL Error" + std::string(alGetString(err)));
		if(buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
		return;
	}

	m_buffer = buffer;
}