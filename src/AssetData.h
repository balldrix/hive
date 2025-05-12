#pragma once

#include "AssetType.h"

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

struct AssetData
{
	std::string id = {};
	std::string path = {};
	AssetType::Type type = AssetType::Type::None;
	std::string tag = {};
};

namespace nlohmann 
{
	static inline void from_json(const json& j, AssetData& data)
	{
		data.id = j.at("id");
		data.path = j.at("path");
		data.tag = j.at("tag");

		std::string typeString = j.at("type");
		AssetType::Type type = AssetType::GetMappedType(typeString);

		if(type != AssetType::Type::None)
			data.type = type;
	}
}