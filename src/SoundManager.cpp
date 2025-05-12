#include "SoundManager.h"

#include "Sound.h"

#include <filesystem>
#include <map>
#include <string>
#include <utility>

SoundManager::SoundManager() { }

SoundManager::~SoundManager() { }

void SoundManager::AddSound(const std::string &filename)
{
	if(!GetSound(filename))
	{
		Sound* sound = new Sound();

		sound->LoadFromWav(filename.c_str());

		std::filesystem::path p(filename);
		std::string name = p.stem().string();

		s_sounds.insert(std::make_pair(name, sound));
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

void SoundManager::Destroy()
{
	for(auto i = s_sounds.begin(); i != s_sounds.end(); ++i)
	{
		delete i->second;
	}
}