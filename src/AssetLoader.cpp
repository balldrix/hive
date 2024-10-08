#include "AssetLoader.h"

#include "pch.h"

std::shared_ptr<AssetLoader> AssetLoader::s_assetLoader;

AssetLoader::AssetLoader() :
	m_assetData(0)
{
}

void AssetLoader::Init(std::string fileName)
{
	s_assetLoader = std::make_shared<AssetLoader>();

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

void AssetLoader::LoadUIAssetsWithTag(std::string tag)
{

}
