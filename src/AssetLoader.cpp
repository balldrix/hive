#include "AssetLoader.h"

#include "AssetData.h"
#include "AssetType.h"
#include "Graphics.h"
#include "Logger.h"
#include "PixelTexture.h"
#include "Sound.h"
#include "Texture.h"
#include "Utils.h"

#include <directxtk/SpriteFont.h>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

std::shared_ptr<AssetLoader> AssetLoader::s_assetLoader;

AssetLoader::AssetLoader() :
	m_graphics(nullptr),
	m_assetData(0),
	m_assetsToLoad(0),
	m_textureAssets(),
	m_spriteFontAssets()
{
}

void AssetLoader::Init(Graphics* graphics, std::string fileName)
{
	Logger::LogInfo("Initialising Asset Loader.");

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

	PixelTexture* pixelTexture = new PixelTexture();
	pixelTexture->Init(graphics);

	s_assetLoader->m_textureAssets.insert({ "t_pixel", pixelTexture });
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

void AssetLoader::CleanupAssetsWithTag(std::string tag)
{
	Logger::LogInfo(fmt::format("Cleaning up assets with tag: {}.", tag));

	s_assetLoader->DeleteTextures(tag);
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
	case AssetType::Type::SpriteFontAsset :
		s_assetLoader->LoadSpriteFont(asset);
		s_assetLoader->m_assetsToLoad.pop_front();
		break;
	case AssetType::Type::SoundFX :
		s_assetLoader->LoadSound(asset);
		s_assetLoader->m_assetsToLoad.pop_front();
		break;
	default:
		break;
	}
}

Texture* AssetLoader::GetTexture(const std::string& id)
{
	for(auto it = s_assetLoader->m_textureAssets.begin(); it != s_assetLoader->m_textureAssets.end(); ++it)
	{
		if((*it).first == id)
			return (*it).second;
	}

	Logger::LogWarning(fmt::format("No texture found in AssetLoader with id {}", id));
	return nullptr;
}

SpriteFont* AssetLoader::GetSpriteFont(const std::string& id)
{
	for(auto it = s_assetLoader->m_spriteFontAssets.begin(); it != s_assetLoader->m_spriteFontAssets.end(); ++it)
	{
		if((*it).first == id)
			return (*it).second;
	}

	Logger::LogWarning(fmt::format("No sprite font found in AssetLoader with id {}", id));
	return nullptr;
}

Sound* AssetLoader::GetSound(const std::string& id)
{
	std::map<std::string, Sound*>::iterator soundIterator = s_assetLoader->m_sounds.find(id);
	if(soundIterator != s_assetLoader->m_sounds.end())
	{
		return soundIterator->second;
	}

	Logger::LogWarning(fmt::format("No sound found in AssetLoader with id {}", id));
	return nullptr;
}

void AssetLoader::OnDeviceLost()
{
	for (auto it = s_assetLoader->m_textureAssets.begin(); it != s_assetLoader->m_textureAssets.end(); ++it)
	{
		(*it).second->Release();
	}
}

void AssetLoader::AddToLoadList(const AssetData& data)
{
	m_assetsToLoad.push_back(data);
}

void AssetLoader::LoadTexture(AssetData asset)
{
	Logger::LogInfo(fmt::format("Loading Texture: {}.", asset.id));

	Texture* texture = new Texture();
	texture->LoadTexture(m_graphics, asset.path);

	m_textureAssets.insert({ {asset.id, texture} });
}

void AssetLoader::LoadSpriteFont(AssetData asset)
{
	Logger::LogInfo(fmt::format("Loading Sprite Font: {}.", asset.id));

	std::wstring path = Utils::ToWideString(asset.path);
	SpriteFont* spriteFont = new SpriteFont(m_graphics->GetDevice().Get(), path.c_str());

	if(spriteFont != nullptr) 
	{
		m_spriteFontAssets.insert({ {asset.id, spriteFont}});
		return;
	}

	std::string error = " Error Loading Sprite Font file " + asset.path + " in AssetLoader.cpp line 114.";
	Logger::LogError(error);
	MessageBox(m_graphics->GetHwnd(), L"Error loading Sprite Font. See Logs/Error.txt", L"Error!", MB_OK);
	PostQuitMessage(0);
}

void AssetLoader::LoadSound(AssetData asset)
{
	std::filesystem::path p(asset.path);
	std::string id = p.stem().string();

	if(!GetSound(id))
	{
		Sound* sound = new Sound();

		sound->LoadFromWav(asset.path.c_str());

		s_assetLoader->m_sounds.insert(std::make_pair(id, sound));
	}
}

void AssetLoader::Destroy()
{
	Logger::LogInfo("Shutting down Asset Loader");
	
	s_assetLoader->DeleteTextures();
	s_assetLoader->DeleteSpriteFonts();
	s_assetLoader->DeleteSounds();
}

void AssetLoader::DeleteTextures()
{
	for(std::pair<std::string, Texture*> pair : m_textureAssets)
	{
		pair.second->Release();
		
		delete pair.second;
		pair.second = nullptr;
	}

	m_textureAssets.clear();
}

void AssetLoader::DeleteTextures(std::string tag)
{
	for(AssetData asset : m_assetData)
	{
		if(asset.tag != tag) continue;

		auto texture = m_textureAssets.find(asset.id);

		if(texture == m_textureAssets.end()) continue;

		texture->second->Release();
		
		delete texture->second;
		texture->second = nullptr;

		m_textureAssets.erase(texture->first);
	}
}

void AssetLoader::DeleteSpriteFonts()
{
	for(std::pair<std::string, SpriteFont*> pair : m_spriteFontAssets)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	m_textureAssets.clear();
}

void AssetLoader::DeleteSounds()
{
	for(auto i = s_assetLoader->m_sounds.begin(); i != s_assetLoader->m_sounds.end(); ++i)
	{
		delete i->second;
	}
}

void AssetLoader::DeleteSounds(std::string tag)
{
	for(AssetData asset : m_assetData)
	{
		if(asset.tag != tag) continue;

		auto pair = m_sounds.find(asset.id);

		if(pair == m_sounds.end()) continue;

		delete pair->second;
		pair->second = nullptr;

		m_sounds.erase(pair->first);
	}
}
