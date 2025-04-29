#include "SoundManager.h"

#include <filesystem>

SoundManager::SoundManager() { }

SoundManager::~SoundManager() { }

void SoundManager::AddSound(const std::wstring &filename)
{
	if(!GetSound(filename))
	{
		Sound* sound = new Sound();

		std::string narrow = std::string(filename.begin(), filename.end());

		sound->LoadFromWav(narrow.c_str());

		std::filesystem::path p(filename);
		std::wstring name = p.stem();

		s_sounds.insert(std::make_pair(name, sound));
	}
}

Sound* SoundManager::GetSound(const std::wstring &name)
{
	std::map<std::wstring, Sound*>::iterator soundIterator = s_sounds.find(name);
	if(soundIterator != s_sounds.end())
		return soundIterator->second;
	else
		return nullptr;
}

void SoundManager::Destroy()
{
	for(std::map<std::wstring, Sound*>::iterator i = s_sounds.begin(); i != s_sounds.end(); ++i)
	{
		delete i->second;
	}
}