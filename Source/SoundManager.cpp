#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::AddSound(const std::string &filename)
{
	if(!GetSound(filename))
	{
		Sound* sound = new Sound();
		sound->LoadFromWav(filename.c_str());

		std::string name = filename.substr(filename.length() - 3, 3);
		s_sounds.insert(make_pair(name, sound));
	}
}

Sound* SoundManager::GetSound(const std::string &name)
{
	std::map<std::string, Sound*>::iterator soundIterator = s_sounds.find(name);
	if(soundIterator != s_sounds.end())
		return soundIterator->second;
	else
		return nullptr;
}

void SoundManager::DeleteSounds()
{
	for(std::map<std::string, Sound*>::iterator i = s_sounds.begin(); i != s_sounds.end(); ++i)
	{
		delete i->second;
	}
}