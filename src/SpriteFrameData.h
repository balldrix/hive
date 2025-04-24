#pragma once

#include <DirectXTK/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <string>
#include <Windows.h>

using json = nlohmann::json;
using namespace DirectX::SimpleMath;

struct SpriteFrameData
{
	std::string filename = {};
	RECT frame = {};
	bool rotated = {};
	bool trimmed = {};
	RECT spriteSourceSize = {};
	Vector2	sourceSize = {};
	float duration = {};

	SpriteFrameData() = default;
};

namespace nlohmann
{
	static inline void from_json(const json& j, SpriteFrameData& s)
	{
		s.filename = j.at("filename").get<std::string>();

		json rect = j.at("frame");
		s.frame.left = rect.at("x");
		s.frame.top = rect.at("y");
		s.frame.right = s.frame.left + rect.at("w");
		s.frame.bottom = s.frame.top + rect.at("h");

		s.rotated = j.at("rotated");
		s.trimmed = j.at("trimmed");

		rect = j.at("spriteSourceSize");
		s.spriteSourceSize.left = rect.at("x");
		s.spriteSourceSize.top = rect.at("y");
		s.spriteSourceSize.right = s.spriteSourceSize.left + rect.at("w");
		s.spriteSourceSize.bottom = s.spriteSourceSize.top + rect.at("h");

		json size = j.at("sourceSize");
		s.sourceSize.x = size.at("w");
		s.sourceSize.y = size.at("h");

		s.duration = j.at("duration");
	}
}