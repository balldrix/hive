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
	~AssetLoader() = default;

	static void Init(Graphics* graphics, std::string filename);
	static void PreWarmAssetsWithTag(std::string tag);
	static void LoadAllPrewarmedAssets();
	static bool IsLoadingDone() { return s_assetLoader->m_assetsToLoad.empty(); }

private:
	void AddToLoadList(const AssetData& data);
	void LoadTexture(AssetData asset);

	typedef std::map<std::string, Texture> TextureAssets;

	static std::shared_ptr<AssetLoader> s_assetLoader;

	std::vector<AssetData> m_assetData;
	std::list<AssetData> m_assetsToLoad;
	TextureAssets m_textureAssets;
	Graphics* m_graphics;
};