#pragma once

#include <AL/al.h>

class Sound
{
friend class SoundManager;
public:
	ALuint GetBuffer() { return m_buffer; }

protected:
	Sound();
	~Sound();
	
	void LoadFromWav(const char* filename);
	ALuint m_buffer;
};