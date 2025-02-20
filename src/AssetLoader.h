#pragma once

#include "AssetData.h"
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

	static Texture* GetTexture(std::string id);
	static SpriteFont* GetSpriteFont(std::string id);

	static void OnDeviceLost();

	static void Shutdown();

private:
	void AddToLoadList(const AssetData& data);
	void LoadTexture(AssetData asset);
	void LoadSpriteFont(AssetData asset);

	void DeleteTextures();
	void DeleteTextures(std::string tag);
	void DeleteSpriteFonts();

	typedef std::map<std::string, Texture*> TextureAssets;
	typedef std::map<std::string, SpriteFont*> SpriteFontAssets;

	static std::shared_ptr<AssetLoader> s_assetLoader;

	Graphics* m_graphics;
	std::vector<AssetData> m_assetData;
	std::list<AssetData> m_assetsToLoad;
	TextureAssets m_textureAssets;
	SpriteFontAssets m_spriteFontAssets;
};