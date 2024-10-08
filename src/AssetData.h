#pragma once

#include "pch.h"

namespace 
{
	struct AssetData
	{
		int id = {};
		std::string path = {};
		std::string tag = {};
	};

	void from_json(const json& j, AssetData& data)
	{
		data.id = j["id"];
		data.path = j["path"];
		data.tag = j["tag"];
	}
}