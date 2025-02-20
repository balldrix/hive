#pragma once

#include "AssetType.h"

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace
{
	struct AssetData
	{
		std::string id = {};
		std::string path = {};
		AssetType::Type type;
		std::string tag = {};
	};

	void from_json(const json& j, AssetData& data)
	{
		data.id = j["id"];
		data.path = j["path"];
		data.tag = j["tag"];

		std::string typeString = j["type"];
		AssetType::Type type = AssetType::GetMappedType(typeString);

		if(type != AssetType::Type::None)
			data.type = type;
	}
}