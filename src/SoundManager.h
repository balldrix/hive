#pragma once

#include "Sound.h"

#include <map>
#include <string>

class SoundManager
{
public:
	static void AddSound(const std::string& filename);
	static Sound* GetSound(const std::string& name);

	static void Destroy();
protected:
	SoundManager();
	~SoundManager();

	static std::map<std::string, Sound*> s_sounds;
};