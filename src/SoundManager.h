#pragma once

#include "Sound.h"

#include <map>
#include <string>

class SoundManager
{
public:
	static void AddSound(const std::wstring& filename);
	static Sound* GetSound(const std::wstring& name);

	static void Destroy();
protected:
	SoundManager();
	~SoundManager();

	static std::map<std::wstring, Sound*> s_sounds;
};