#pragma once

#include "pch.h"


class AssetType
{
public:
	enum class Type
	{
		TextureAsset = 0,
		None
	};

	typedef std::map<std::string, Type> AssetTypeMap;

	static Type GetMappedType(std::string key);

private:

	static AssetTypeMap s_assetTypeMap;
};