#include "AudioEngine.h"

#include <AL/alc.h>
#include <stdexcept>

AudioEngine* AudioEngine::s_instance = nullptr;

void AudioEngine::Init(unsigned int channels)
{
	if(s_instance == nullptr)
		s_instance = new AudioEngine(channels);	
}

AudioEngine::AudioEngine(unsigned int channels)
{
	m_alcDevice = alcOpenDevice(nullptr);
	if(m_alcDevice == nullptr)
		throw std::exception();

	m_alcContext = alcCreateContext(m_alcDevice, nullptr);
	if(m_alcContext == nullptr)
		throw std::exception();

	if(!alcMakeContextCurrent(m_alcContext))
		throw std::exception();
}

AudioEngine::~AudioEngine()
{
	alcMakeContextCurrent(nullptr);
	// TODO: delete sources
	alcDestroyContext(m_alcContext);
	alcCloseDevice(m_alcDevice);
}