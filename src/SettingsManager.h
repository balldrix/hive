#pragma once

#include "simpleini.h"

class SettingsManager
{
public:
	static SettingsManager* Instance() { return s_instance; }

	static void Init();
	static void Destroy();

	void Save();

	float GetSFXVolume() const;
	float GetMusicVolume() const;
	int GetScreenWidth() const;
	int GetScreenHeight() const;
	bool IsFullscreen() const;

	void SetSFXVolume(float volume);
	void SetMusicVolume(float volume);
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
	void SetFullscreen(bool fullscreen);

private:
	static SettingsManager* s_instance;

	SettingsManager();
	void Load();

	CSimpleIniA m_ini;
};