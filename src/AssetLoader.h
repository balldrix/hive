#pragma once

#include "AssetData.h"
#include "Sound.h"
#include "Texture.h"

#include <directxtk/SpriteFont.h>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace DirectX;

class Graphics;

class AssetLoader
{
public:
	AssetLoader();
	~AssetLoader() {};

	static void Init(Graphics* graphics, std::string filename);
	static void PreWarmAssetsWithTag(std::string tag);
	static void CleanupAssetsWithTag(std::string tag);
	static void LoadAllPrewarmedAssets();
	static bool IsLoadingDone() { return s_assetLoader->m_assetsToLoad.empty(); }

	static Texture* GetTexture(const std::string& id);
	static SpriteFont* GetSpriteFont(const std::string& id);
	static Sound* GetSound(const std::string& id);
	static void OnDeviceLost();

	static void Destroy();

private:
	void AddToLoadList(const AssetData& data);
	void LoadTexture(AssetData asset);
	void LoadSpriteFont(AssetData asset);
	void LoadSound(AssetData asset);

	void DeleteTextures();
	void DeleteTextures(std::string tag);
	void DeleteSpriteFonts();
	void DeleteSounds();
	void DeleteSounds(std::string tag);

	typedef std::map<std::string, Texture*> TextureAssets;
	typedef std::map<std::string, SpriteFont*> SpriteFontAssets;
	typedef std::map<std::string, Sound*> SoundAssets;

	static std::shared_ptr<AssetLoader> s_assetLoader;

	Graphics* m_graphics;
	std::vector<AssetData> m_assetData;
	std::list<AssetData> m_assetsToLoad;
	TextureAssets m_textureAssets;
	SpriteFontAssets m_spriteFontAssets;
	SoundAssets m_sounds;
};