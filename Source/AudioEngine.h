#pragma once

class ALCdevice;
class ALCcontext;

class AudioEngine
{
public:
	static AudioEngine* Instance() { return m_instance; }
	static void Init(unsigned int channels = 32);

private:
	AudioEngine(unsigned int channels = 32);
	~AudioEngine();
	
	static AudioEngine* m_instance;

	ALCdevice* m_alcDevice;
	ALCcontext* m_alcContext;
};