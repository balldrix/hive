#pragma once

#include <DirectXTK/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
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

inline void from_json(const json& j, SpriteFrameData& s)
{
	s.filename = j.at("filename").get<std::string>();

	json rect = j["frame"];
	s.frame.left = rect["x"];
	s.frame.top = rect["y"];
	s.frame.right = s.frame.left + rect["w"];
	s.frame.bottom = s.frame.top + rect["h"];

	s.rotated = j["rotated"];
	s.trimmed = j["trimmed"];

	rect = j["spriteSourceSize"];
	s.spriteSourceSize.left = rect["x"];
	s.spriteSourceSize.top = rect["y"];
	s.spriteSourceSize.right = s.spriteSourceSize.left + rect["w"];
	s.spriteSourceSize.bottom = s.spriteSourceSize.top + rect["h"];

	json size = j["sourceSize"];
	s.sourceSize.x = size["w"];
	s.sourceSize.y = size["h"];

	s.duration = j["duration"];
}