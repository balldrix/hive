#include "AssetType.h"

AssetType::AssetTypeMap AssetType::s_assetTypeMap = {
	{ "texture", Type::TextureAsset },
	{ "spritefont", Type::SpriteFontAsset },
	{ "hitbox", Type::HitBoxData },
	{ "spritesheet", Type::SpritesheetData },
	{ "audio", Type::Audio }
};

AssetType::Type AssetType::GetMappedType(std::string key)
{
	auto result = std::find_if(
		s_assetTypeMap.begin(),
		s_assetTypeMap.end(),
		[key](const auto& mo) { return mo.first == key; });

	if(result != s_assetTypeMap.end())
		return result->second;

	return AssetType::Type::None;
}
