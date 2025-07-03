#include "SettingsManager.h"
#include "Logger.h"

#include <string>
#include "UIOptionsView.h"

static const std::string Filename = "config.cfg";

SettingsManager* SettingsManager::s_instance = nullptr;

SettingsManager::SettingsManager()
{
	m_ini.SetUnicode();
}

void SettingsManager::Init()
{
	s_instance = new SettingsManager();

	Logger::LogInfo("Initialising SettingsManager.");
	s_instance->Load();
}

void SettingsManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void SettingsManager::Load()
{
	SI_Error rc = m_ini.LoadFile(Filename.c_str());

	if(!m_ini.GetDoubleValue("Audio", "MusicVolume"))
		m_ini.SetDoubleValue("Audio", "MusicVolume", 0.75);

	if(!m_ini.GetDoubleValue("Audio", "SFXVolume"))
		m_ini.SetDoubleValue("Audio", "SFXVolume", 0.6);

	if(!m_ini.GetLongValue("Display", "ScreenWidth"))
		m_ini.SetLongValue("Display", "ScreenWidth", 1280);

	if(!m_ini.GetLongValue("Display", "ScreenHeight"))
		m_ini.SetLongValue("Display", "ScreenHeight", 720);

	if(!m_ini.GetBoolValue("Display", "Fullscreen"))
		m_ini.SetBoolValue("Display", "Fullscreen", false);

	m_ini.SaveFile(Filename.c_str());
}

void SettingsManager::Save()
{
	m_ini.SaveFile(Filename.c_str());
}

float SettingsManager::GetMusicVolume() const {
	return static_cast<float>(m_ini.GetDoubleValue("Audio", "MusicVolume", 0.75));
}
float SettingsManager::GetSFXVolume() const {
	return static_cast<float>(m_ini.GetDoubleValue("Audio", "SFXVolume", 0.6));
}
int SettingsManager::GetScreenWidth() const {
	return static_cast<int>(m_ini.GetLongValue("Graphics", "ScreenWidth", 1280));
}
int SettingsManager::GetScreenHeight() const {
	return static_cast<int>(m_ini.GetLongValue("Graphics", "ScreenHeight", 720));
}
bool SettingsManager::IsFullscreen() const {
	return m_ini.GetBoolValue("Graphics", "Fullscreen", false);
}

void SettingsManager::SetMusicVolume(float volume) {
	m_ini.SetDoubleValue("Audio", "MusicVolume", volume);
}
void SettingsManager::SetSFXVolume(float volume) {
	m_ini.SetDoubleValue("Audio", "SFXVolume", volume);
}
void SettingsManager::SetScreenWidth(int width) {
	m_ini.SetLongValue("Graphics", "ScreenWidth", width);
}
void SettingsManager::SetScreenHeight(int height) {
	m_ini.SetLongValue("Graphics", "ScreenHeight", height);
}
void SettingsManager::SetFullscreen(bool fullscreen) {
	m_ini.SetBoolValue("Graphics", "Fullscreen", fullscreen);
}