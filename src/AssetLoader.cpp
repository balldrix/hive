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
	Logger::LogInfo(fmt::format("Prewarming Loading of assets with tag: {}.", tag));

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

	switch (asset.type)
	{
	case AssetType::Type::TextureAsset :
		s_assetLoader->LoadTexture(asset);
		s_assetLoader->m_assetsToLoad.pop_front();
			break;
	case AssetType::Type::SpriteFontAsset:
		s_assetLoader->LoadSpriteFont(asset);
		s_assetLoader->m_assetsToLoad.pop_front();
		break;
	default:
		break;
	}
}

Texture* AssetLoader::GetTexture(std::string name)
{
	for(auto it = s_assetLoader->m_textureAssets.begin(); it != s_assetLoader->m_textureAssets.end(); ++it)
	{
		if((*it).first == name)
			return (*it).second;
	}

	Logger::LogWarning(fmt::format("No texture found in AssetLoader with name {}", name));
	return nullptr;
}

SpriteFont* AssetLoader::GetSpriteFont(std::string name)
{
	for(auto it = s_assetLoader->m_spriteFontAssets.begin(); it != s_assetLoader->m_spriteFontAssets.end(); ++it)
	{
		if((*it).first == name)
			return (*it).second;
	}

	Logger::LogWarning(fmt::format("No sprite font found in AssetLoader with name {}", name));
	return nullptr;
}

void AssetLoader::AddToLoadList(const AssetData& data)
{
	m_assetsToLoad.push_back(data);
}

void AssetLoader::LoadTexture(AssetData asset)
{
	Logger::LogInfo(fmt::format("Loading Texture: {}.", asset.name));

	Texture* texture = new Texture();
	texture->LoadTexture(m_graphics, asset.path);

	m_textureAssets.insert({ {asset.name, texture} });
}

void AssetLoader::LoadSpriteFont(AssetData asset)
{
	Logger::LogInfo(fmt::format("Loading Sprite Font: {}.", asset.name));

	auto path = std::wstring(asset.path.begin(), asset.path.end());
	SpriteFont* spriteFont = new SpriteFont(m_graphics->GetDevice().Get(), path.c_str());

	if(spriteFont != nullptr) 
	{
		m_spriteFontAssets.insert({ {asset.name, spriteFont}});	
		return;
	}

	std::string error = " Error Loading Sprite Font file " + asset.path + " in AssetLoader.cpp line 114.";
	Logger::LogError(error);
	MessageBox(m_graphics->GetHwnd(), L"Error loading Sprite Font. See Logs/Error.txt", L"Error!", MB_OK);
	PostQuitMessage(0);
}

void AssetLoader::Shutdown()
{
	Logger::LogInfo("Shutting down Asset Loader");
	
	s_assetLoader->DeleteTextures();
	s_assetLoader->DeleteSpriteFonts();
}

void AssetLoader::DeleteTextures()
{
	for (std::pair<std::string, Texture*> pair : m_textureAssets)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}

	m_textureAssets.clear();
}

void AssetLoader::DeleteSpriteFonts()
{
	for (std::pair<std::string, Texture*> pair : m_textureAssets)
	{
		pair.second->Release();
		delete pair.second;
		pair.second = nullptr;
	}

	m_textureAssets.clear();
}
