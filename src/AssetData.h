#pragma once

#include "AssetType.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace
{
	struct AssetData
	{
		int id = {};
		std::string name = {};
		std::string path = {};
		AssetType::Type type;
		std::string tag = {};
	};

	void from_json(const json& j, AssetData& data)
	{
		data.id = j["id"];
		data.name = j["name"];
		data.path = j["path"];
		data.tag = j["tag"];

		std::string typeString = j["type"];
		AssetType::Type type = AssetType::GetMappedType(typeString);

		if(type != AssetType::Type::None)
			data.type = type;
	}
}