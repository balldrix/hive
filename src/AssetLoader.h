#pragma once

#include "pch.h"
#include "AssetData.h"
#include "AssetType.h"
#include "Texture.h"

class Graphics;

class AssetLoader
{
public:	
	AssetLoader();
	~AssetLoader() {};

	static void Init(Graphics* graphics, std::string filename);
	static void PreWarmAssetsWithTag(std::string tag);
	static void LoadAllPrewarmedAssets();
	static bool IsLoadingDone() { return s_assetLoader->m_assetsToLoad.empty(); }

	static Texture* GetTexture(std::string name);
	static SpriteFont* GetSpriteFont(std::string name);

	static void Shutdown();

private:
	void AddToLoadList(const AssetData& data);
	void LoadTexture(AssetData asset);
	void LoadSpriteFont(AssetData asset);
	void DeleteTextures();
	void DeleteSpriteFonts();

	typedef std::map<std::string, Texture*> TextureAssets;
	typedef std::map<std::string, SpriteFont*> SpriteFontAssets;

	static std::shared_ptr<AssetLoader> s_assetLoader;

	std::vector<AssetData> m_assetData;
	std::list<AssetData> m_assetsToLoad;
	TextureAssets m_textureAssets;
	SpriteFontAssets m_spriteFontAssets;
	Graphics* m_graphics;
};