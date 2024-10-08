#pragma once

#include "pch.h"
#include "AssetData.h"

class Sprite;

class AssetLoader
{
public:
	AssetLoader();
	static void Init(std::string filename);
	static void LoadUIAssetsWithTag(std::string tag);

private:
	static std::shared_ptr<AssetLoader> s_assetLoader;

	std::vector<AssetData> m_assetData;
};

