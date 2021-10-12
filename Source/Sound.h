#pragma once

#include <AL/al.h>

class Sound
{
friend class SoundManager;
public:

	float GetLength() { return m_length; }
	int GetBitrate() { return m_bitrate; }
	int GetSampleRate() { return m_samplerate; }
	int GetSize() { return m_size; }
	int GetChannels() { return m_channels; }

	ALuint GetBuffer() { return m_buffer; }

protected:
	Sound();
	~Sound();
	
	void LoadFromWav(const char* filename);
	
	float m_length;
	int m_bitrate;
	int m_samplerate;
	int m_size;
	int m_channels;

	ALuint m_buffer;
};