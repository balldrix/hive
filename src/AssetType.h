#pragma once

#include <map>
#include <string>

class AssetType
{
public:
	enum class Type
	{
		TextureAsset = 0,
		SpriteFontAsset,
		HitBoxData,
		DamageData,
		SpritesheetData,
		None
	};

	typedef std::map<std::string, Type> AssetTypeMap;

	static Type GetMappedType(std::string key);

private:

	static AssetTypeMap s_assetTypeMap;
};