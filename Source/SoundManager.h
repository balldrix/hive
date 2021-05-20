#pragma once

#include <map>
#include <string>
#include "Sound.h"

class SoundManager
{
public:
	static void AddSound(const std::string &filename);
	static Sound* GetSound(const std::string &name);

	static void DeleteSounds();
protected:
	SoundManager();
	~SoundManager();

	static std::map<std::string, Sound*> s_sounds;
};