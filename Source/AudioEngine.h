#pragma once

class ALCdevice;
class ALCcontext;

class AudioEngine
{
public:
	static AudioEngine* Instance() { return s_instance; }
	static void Init(unsigned int channels = 32);

private:
	AudioEngine(unsigned int channels = 32);
	~AudioEngine();
	
	static AudioEngine* s_instance;

	ALCdevice* m_alcDevice;
	ALCcontext* m_alcContext;
};