#pragma once

#include <AL/al.h>

class Sound
{
	friend class SoundManager;
public:

	float GetLength() const { return m_length; }
	int GetBitrate() const { return m_bitrate; }
	int GetSampleRate() const { return m_samplerate; }
	int GetSize() const { return m_size; }
	int GetChannels() const { return m_channels; }

	ALuint GetBuffer() const { return m_buffer; }

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