#include "AssetLoader.h"

#include "AssetType.h"
#include "Graphics.h"
#include "pch.h"

std::shared_ptr<AssetLoader> AssetLoader::s_assetLoader;

AssetLoader::AssetLoader() :
	m_assetData(0)
{
}

void AssetLoader::Init(Graphics* graphics, std::string fileName)
{
	s_assetLoader = std::make_shared<AssetLoader>();
	s_assetLoader->m_graphics = graphics;

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(fileName);
	}
	catch (std::system_error& e)
	{
		std::string message = fmt::format("{0}, AssetLoader::Init failed. File {1} does not exist.", e.code().message(), fileName);
		Logger::LogError(message);
		return;
	}

	json data = json::parse(file);
	s_assetLoader->m_assetData = data.get<std::vector<AssetData>>();
}

void AssetLoader::PreWarmAssetsWithTag(std::string tag)
{
	Logger::LogInfo(fmt::format("Prewarming Loading of assets with tag: {}", tag));

	std::vector<AssetData> data = s_assetLoader->m_assetData;
	for(auto it = data.begin(); it != data.end(); ++it)
	{
		if(it->tag == tag)
		{
			s_assetLoader->AddToLoadList(*it);
		}
	}
}

void AssetLoader::LoadAllPrewarmedAssets()
{
	AssetData asset = s_assetLoader->m_assetsToLoad.front();

	if(asset.type == AssetType::Type::TextureAsset)
		s_assetLoader->LoadTexture(asset);

	s_assetLoader->m_assetsToLoad.pop_front();
}

Texture* AssetLoader::GetTexture(std::string name)
{
	for(auto it = s_assetLoader->m_textureAssets.begin(); it != s_assetLoader->m_textureAssets.end(); ++it)
	{
		if ((*it).first == name)
			return &(*it).second;
	}

	Logger::LogWarning(fmt::format("No texture found in AssetLoader with name {}", name));
	return nullptr;
}

void AssetLoader::AddToLoadList(const AssetData& data)
{
	m_assetsToLoad.push_back(data);
}

void AssetLoader::LoadTexture(AssetData asset)
{
	Logger::LogInfo(fmt::format("Loading Texture: {}", asset.name));

	Texture texture;
	texture.LoadTexture(m_graphics, asset.path);

	m_textureAssets.insert({ {asset.name, texture} });
}