#pragma once

#include <map>
#include <string>
#include "Sound.h"

class SoundManager
{
public:
	static void AddSound(const std::wstring& filename);
	static Sound* GetSound(const std::wstring& name);

	static void DeleteSounds();
protected:
	SoundManager();
	~SoundManager();

	static std::map<std::wstring, Sound*> s_sounds;
};